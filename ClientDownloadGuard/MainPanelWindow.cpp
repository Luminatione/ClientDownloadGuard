#include <QMessageBox>

#include "MainPanelWindow.h"



MainPanelWindow::MainPanelWindow(QWidget* parent)
{
	ui.setupUi(this);
	initializeIcons();
	ui.currentStateGraphic->setPixmap(noConnection);
	
	setupConnections();
	populateStateSelection();
}
void MainPanelWindow::initializeIcons()
{
	networkIsBusyIcon = QPixmap(":/Graphic/Graphic/close.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	askNotToDownload = QPixmap(":/Graphic/Graphic/exclamation.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	networkIsFree = QPixmap(":/Graphic/Graphic/check.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	noConnection = QPixmap(":/Graphic/Graphic/no-internet.png").scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void MainPanelWindow::setupConnections()
{
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(onAboutTriggered()));
}

void MainPanelWindow::populateStateSelection()
{
	ui.stateSelection->addItems({ "Downloading", "Ask not to download", "Free" });
}

void MainPanelWindow::getState()
{
	
}

void MainPanelWindow::setAuthKey(QString& authKey)
{
	this->authKey = authKey;
}

void MainPanelWindow::onAboutTriggered()
{
	QMessageBox::about(this, "About", "Icons made by <a href=\"https://www.flaticon.com/authors/alfredo-hernandez\" title=\"Alfredo Hernandez\">Alfredo Hernandez</a>, <a href=\"https://www.flaticon.com/authors/good-ware\" title=\"Good Ware\">Good Ware</a> and <a href=\"https://www.flaticon.com/authors/pixelmeetup\" title=\"Pixelmeetup\">Pixelmeetup</a> from <a href=\"https://www.flaticon.com/\" title=\"Flaticon\">www.flaticon.com</a>");
}