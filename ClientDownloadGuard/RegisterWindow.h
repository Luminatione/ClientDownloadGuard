#pragma once
#include <QMainWindow>
#include <ui_mainWindow.h>

class RegisterWindow : public QMainWindow
{
	Q_OBJECT
public:

	RegisterWindow(QWidget* widget = Q_NULLPTR);

	Ui::MainWindowClass ui;

};

