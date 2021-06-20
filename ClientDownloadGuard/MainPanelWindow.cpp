#include <QMessageBox>
#include <QNetworkReply>

#include "QtMacros.h"
#include "MainPanelWindow.h"
#include "ResponseReader.h"
#include "ServerConnectionManager.h"
#include "LabelTextSetter.h"


void MainPanelWindow::initializeLabelTextSetters()
{
	authorLabelTextSetter = LabelTextSetter("", "Author: ", "", ui.authorLabel);
	descriptionLabelTextSetter = LabelTextSetter("", "Description: \n", "", ui.currentDescriptionLabel);
}

MainPanelWindow::MainPanelWindow(QString authKey, QWidget* parent) : authKey(authKey)
{
	ui.setupUi(this);
	initializeIcons();
	ui.currentStateGraphic->setPixmap(noConnection);

	setupConnections();
	populateStateSelection();
	initializeLabelTextSetters();
	getState();
}
void MainPanelWindow::initializeIcons()
{
	networkIsBusyIcon = QPixmap(":/Graphic/Graphic/close.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	askNotToDownloadIcon = QPixmap(":/Graphic/Graphic/exclamation.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	networkIsFreeIcon = QPixmap(":/Graphic/Graphic/check.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	noConnection = QPixmap(":/Graphic/Graphic/no-internet.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void MainPanelWindow::setupConnections()
{
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(onAboutTriggered()));
}

void MainPanelWindow::populateStateSelection()
{
	ui.stateSelection->addItems({  "Free", "Downloading", "Ask not to download" });
}

void MainPanelWindow::getState()
{
	reply = QSharedPointer<QNetworkReply>(ServerConnectionManager::serverConnectionManager->getNetworkState(authKey));
	SERVER_RESPONSE_TO_THIS_CONNECTION(reply, MainPanelWindow::onGetStateResponse, MainPanelWindow::onGetStateError);
}

void MainPanelWindow::setAuthKey(QString& authKey)
{
	this->authKey = authKey;
}

void MainPanelWindow::onAboutTriggered()
{
	QMessageBox::about(this, "About", "Icons made by <a href=\"https://www.flaticon.com/authors/alfredo-hernandez\" title=\"Alfredo Hernandez\">Alfredo Hernandez</a>, <a href=\"https://www.flaticon.com/authors/good-ware\" title=\"Good Ware\">Good Ware</a> and <a href=\"https://www.flaticon.com/authors/pixelmeetup\" title=\"Pixelmeetup\">Pixelmeetup</a> from <a href=\"https://www.flaticon.com/\" title=\"Flaticon\">www.flaticon.com</a>");
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
	default: ui.currentStateGraphic->setPixmap(noConnection);
		break;
	}
}

void MainPanelWindow::onGetStateResponse()
{
	auto [state, value] = ResponseReader::getStateAndValueJsonRefValues(reply.get());
	if (state.toString() == "Success")
	{
		int type = value.toObject()["type"].toInt();
		QString description = value.toObject()["description"].toString();
		QString user = value.toObject()["login"].toString();

		authorLabelTextSetter.setText(user);
		descriptionLabelTextSetter.setText(description);
		setIcon(type);
	}
	else
	{
		ui.statusbar->showMessage(state.toString() + ": " + value.toString());
		ui.currentStateGraphic->setPixmap(noConnection);
	}
}

void MainPanelWindow::onGetStateError(QNetworkReply::NetworkError errorCode)
{
	ui.currentStateGraphic->setPixmap(noConnection);
	ui.statusbar->showMessage("Error: " + errorCode);
}
