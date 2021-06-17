#pragma once

#include <qmainwindow.h>

#include "ui_MainPanelWindow.h"
class MainPanelWindow : public QMainWindow
{
	Q_OBJECT

	Ui::MainPanelWindow ui;
	QPixmap networkIsBusyIcon = QPixmap(":/Graphic/Graphic/close.png");
	QPixmap askNotToDownload = QPixmap(":/Graphic/Graphic/exclamation.png");
	QPixmap networkIsFree = QPixmap(":/Graphic/Graphic/check.png");
public:
	MainPanelWindow(QWidget* parent = Q_NULLPTR);

private slots:
	void onAboutTriggered();
};

