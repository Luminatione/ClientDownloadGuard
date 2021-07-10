#include <QMessageBox>

#include "QtMacros.h"
#include "MainPanelWindow.h"
#include "ResponseReader.h"
#include "ServerConnectionManager.h"
#include "LabelTextSetter.h"
#include "SettingsWindow.h"
#include "AutoDetectionWindow.h"
#include "ScheduleWindow.h"
#include "ScheduleService.h"

void MainPanelWindow::startAutoDetection()
{
	autoDetectionService = new  AutoDetectionService();
	autoDetectionService->setState(networkState);
	autoDetectionService->moveToThread(&autoDetectionThread);
	connect(&autoDetectionThread, &QThread::started, autoDetectionService, &AutoDetectionService::work);
	connect(autoDetectionService, &AutoDetectionService::notify, this, &MainPanelWindow::onNotify);
	connect(autoDetectionService, &AutoDetectionService::refresh, this, &MainPanelWindow::onRefreshClick);
	connect(autoDetectionService, &AutoDetectionService::updateNetworkState, this, &MainPanelWindow::onSetState);
	autoDetectionThread.start();
}

void MainPanelWindow::startSchedule()
{
	scheduleService = new ScheduleService();
	scheduleService->setState(networkState);
	scheduleService->moveToThread(&scheduleThread);
	connect(&scheduleThread, &QThread::started, scheduleService, &ScheduleService::work);
	connect(scheduleService, &ScheduleService::notify, this, &MainPanelWindow::onNotify);
	connect(scheduleService, &ScheduleService::refresh, this, &MainPanelWindow::onRefreshClick);
	connect(scheduleService, &ScheduleService::updateNetworkState, this, &MainPanelWindow::onSetState);
	scheduleThread.start();
}

MainPanelWindow::MainPanelWindow(QString authKey, QWidget* parent) : authKey(authKey)
{
	ui.setupUi(this);
	initializeIcons();
	ui.currentStateGraphic->setPixmap(noConnectionIcon);

	setupConnections();
	populateStateSelection();
	initializeLabelTextSetters();
	getState();
	offlineMode = authKey.isEmpty();
	if (offlineMode)
	{
		ui.statusbar->showMessage("Waiting for server...");
	}
	startAutoDetection();
	startSchedule();
}

MainPanelWindow::~MainPanelWindow()
{
	autoDetectionThread.quit();
}

void MainPanelWindow::initializeLabelTextSetters()
{
	authorLabelTextSetter = LabelTextSetter("", "Author: ", "", ui.authorLabel);
	descriptionLabelTextSetter = LabelTextSetter("", "Description: \n", "", ui.currentDescriptionLabel);
}

void MainPanelWindow::initializeIcons()
{
	networkIsBusyIcon = QPixmap(":/Graphic/Graphic/close.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	askNotToDownloadIcon = QPixmap(":/Graphic/Graphic/exclamation.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	networkIsFreeIcon = QPixmap(":/Graphic/Graphic/check.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	noConnectionIcon = QPixmap(":/Graphic/Graphic/no-internet.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void MainPanelWindow::setupConnections()
{
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(onAboutTriggered()));
	connect(ui.actionSettings, SIGNAL(triggered()), this, SLOT(onSettingsTriggered()));
	connect(ui.actionAuto_detection, SIGNAL(triggered()), this, SLOT(onAutoDetectionTriggered()));
	connect(ui.actionSchedule, SIGNAL(triggered()), this, SLOT(onScheduleTriggered()));
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.confirmButton, setState());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.refreshButton, onRefreshClick());
}

void MainPanelWindow::populateStateSelection()
{
	ui.stateSelection->addItems({ "Free", "Downloading", "Ask not to download" });
}

void MainPanelWindow::getState()
{
	replyGet = QSharedPointer<QNetworkReply>(ServerConnectionManager::serverConnectionManager->getNetworkState(authKey));
	SERVER_RESPONSE_TO_THIS_CONNECTION(replyGet, MainPanelWindow::onGetStateResponse, MainPanelWindow::onGetStateError);
}

void MainPanelWindow::onSetState(int type, QString& description)
{
	if(type == 3)
	{
		return;
	}
	if (offlineMode)
	{
		awaitsSetState = true;
		ui.statusbar->showMessage("Waiting for server");
		return;
	}
	awaitsSetState = false;
	replySet = QSharedPointer<QNetworkReply>(
		ServerConnectionManager::serverConnectionManager->setNetworkState(authKey, type, description));
	SERVER_RESPONSE_TO_THIS_CONNECTION(replySet, MainPanelWindow::onSetStateResponse, MainPanelWindow::onSetStateError);
}

void MainPanelWindow::onNotify(int type, QString& title, QString& text)
{
	QMessageBox::StandardButton result = QMessageBox::question(this, title, text, QMessageBox::Yes | QMessageBox::No);
	if (result == QMessageBox::Yes)
	{
		QString description = "State set automatically";
		onSetState(type, description);
	}
}

void MainPanelWindow::setState()
{
	if (offlineMode)
	{
		awaitsSetState = true;
		ui.statusbar->showMessage("Waiting for server");
		return;
	}
	awaitsSetState = false;
	QString description = ui.descriptionTextEdit->toPlainText();
	replySet = QSharedPointer<QNetworkReply>(
		ServerConnectionManager::serverConnectionManager->setNetworkState(
			authKey, ui.stateSelection->currentIndex(), description));
	SERVER_RESPONSE_TO_THIS_CONNECTION(replySet, MainPanelWindow::onSetStateResponse, MainPanelWindow::onSetStateError);
}

void MainPanelWindow::setAuthKey(QString& authKey)
{
	this->authKey = authKey;
}

void MainPanelWindow::onAboutTriggered()
{
	QMessageBox::about(this, "About", "Icons made by <a href=\"https://www.flaticon.com/authors/alfredo-hernandez\" title=\"Alfredo Hernandez\">Alfredo Hernandez</a>, <a href=\"https://www.flaticon.com/authors/good-ware\" title=\"Good Ware\">Good Ware</a> and <a href=\"https://www.flaticon.com/authors/pixelmeetup\" title=\"Pixelmeetup\">Pixelmeetup</a> from <a href=\"https://www.flaticon.com/\" title=\"Flaticon\">www.flaticon.com</a>");
}

void MainPanelWindow::onSettingsTriggered()
{
	SettingsWindow* settingsWindow = new SettingsWindow();
	settingsWindow->setWindowModality(Qt::ApplicationModal);
	settingsWindow->setAndShowAuthKey(authKey);
	settingsWindow->show();
}

void MainPanelWindow::onAutoDetectionTriggered()
{
	AutoDetectionWindow* autoDetectionWindow = new AutoDetectionWindow();
	//QObject::connect(autoDetectionWindow, &AutoDetectionWindow::destroyed, autoDetectionService, &AutoDetectionService::loadAutoDetectedWindows); //<--- this doesn't work for some reason
	connect(autoDetectionWindow, &AutoDetectionWindow::destroyed, [&] {autoDetectionService->loadAutoDetectedWindows(); });
	autoDetectionWindow->setAttribute(Qt::WA_DeleteOnClose);
	autoDetectionWindow->show();
}

void MainPanelWindow::onScheduleTriggered()
{
	ScheduleWindow* scheduleWindow = new ScheduleWindow();
	connect(scheduleWindow, &ScheduleWindow::destroyed, [&] {scheduleService->loadSchedule(); });
	scheduleWindow->setWindowModality(Qt::WindowModal);
	scheduleWindow->setAttribute(Qt::WA_DeleteOnClose);
	scheduleWindow->show();
}

void MainPanelWindow::setIcon(int type)
{
	switch (type)
	{
	case 0: ui.currentStateGraphic->setPixmap(networkIsFreeIcon);
		break;
	case 1: ui.currentStateGraphic->setPixmap(networkIsBusyIcon);
		break;
	case 2: ui.currentStateGraphic->setPixmap(askNotToDownloadIcon);
		break;
	default: ui.currentStateGraphic->setPixmap(noConnectionIcon);
		break;
	}
}

void MainPanelWindow::becomeOnline()
{
	offlineMode = false;
	getState();
	if (awaitsSetState)
	{
		setState();
	}
}

void MainPanelWindow::onGetStateResponse()
{
	auto [state, value] = ResponseReader::getStateAndValueJsonRefValues(replyGet.get());
	if (state.toString() == "Success")
	{
		int type = value.toObject()["type"].toInt();
		QString description = value.toObject()["description"].toString();
		QString user = value.toObject()["login"].toString();

		authorLabelTextSetter.setText(user);
		descriptionLabelTextSetter.setText(description);
		setIcon(type);
		networkState = static_cast<enum state>(type);
		autoDetectionService->setState(networkState);
	}
	else
	{
		ui.statusbar->showMessage(state.toString() + ": " + value.toString());
		ui.currentStateGraphic->setPixmap(noConnectionIcon);
	}
}

void MainPanelWindow::onGetStateError(QNetworkReply::NetworkError errorCode)
{
	ui.currentStateGraphic->setPixmap(noConnectionIcon);
	ui.statusbar->showMessage("Error: " + QString::number(errorCode));
	networkState = no_connection;
	autoDetectionService->setState(networkState);
}

void MainPanelWindow::onSetStateResponse()
{
	auto [state, value] = ResponseReader::getStateAndValueQStrings(replySet.get());
	if (state == "Success")
	{
		ui.statusbar->showMessage(state);
		getState();
	}
	else
	{
		ui.statusbar->showMessage(state + ": " + value);
		ui.currentStateGraphic->setPixmap(noConnectionIcon);
	}
}

void MainPanelWindow::onSetStateError(QNetworkReply::NetworkError errorCode)
{
	ui.statusbar->showMessage("Error: " + QString::number(errorCode));
}

void MainPanelWindow::onRefreshClick()
{
	getState();
}
