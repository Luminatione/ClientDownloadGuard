#include <QMessageBox>

#include "MainPanelWindow.h"

MainPanelWindow::MainPanelWindow(QWidget* parent)
{
	ui.setupUi(this);
	QPixmap pixmap = QPixmap(":/Graphic/Graphic/close.png");
	pixmap = pixmap.scaled(ui.currentStateGraphic->width(), ui.currentStateGraphic->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.currentStateGraphic->setPixmap(pixmap);
	
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(onAboutTriggered()));

	ui.stateSelection->addItems({ "Downloading", "Ask not to download", "Free" });
}

void MainPanelWindow::onAboutTriggered()
{
	QMessageBox::about(this, "About", "Icons made by <a href=\"https://www.flaticon.com/authors/alfredo-hernandez\" title=\"Alfredo Hernandez\">Alfredo Hernandez</a> and <a href=\"https://www.flaticon.com/authors/pixelmeetup\" title=\"Pixelmeetup\">Pixelmeetup</a> from <a href=\"https://www.flaticon.com/\" title=\"Flaticon\">www.flaticon.com</a>");
}
