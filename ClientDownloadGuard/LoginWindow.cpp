#include "LoginWindow.h"
#include "QtMacros.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	setupConnections();
}

void LoginWindow::setupConnections()
{
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.LoginButton, onLoginClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.QuitButton, onQuitClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.RegisterButton, onRegisterClick());
}

void LoginWindow::onLoginClick()
{
	ui.statusBar->showMessage("Logging...");
}

void LoginWindow::onQuitClick()
{
	QApplication::quit();
}

void LoginWindow::onRegisterClick()
{
	
}
