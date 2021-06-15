#include "RegisterWindow.h"

#include "LoginWindow.h"
#include "QtMacros.h"
RegisterWindow::RegisterWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setupConnections();

	ui.registerButton->setEnabled(false);
}

RegisterWindow::~RegisterWindow()
{
}

void RegisterWindow::setupConnections()
{
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.loginButton, onLoginClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.quitButton, onQuitClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.registerButton, onRegisterClick());
	connect(ui.usernameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onCredentialsTextChanged()));
	connect(ui.passwordLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onCredentialsTextChanged()));
	connect(ui.repeatPasswordLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onCredentialsTextChanged()));
}

bool RegisterWindow::isUsernameAndPasswordValid()
{
	return usernameValidator->isValid(ui.usernameLineEdit->text()) && passwordValidator->isValid(
		ui.passwordLineEdit->text()) && ui.passwordLineEdit->text() == ui.repeatPasswordLineEdit->text();
}

void RegisterWindow::onQuitClick()
{
	QApplication::quit();
}

void RegisterWindow::onLoginClick()
{
	LoginWindow* loginWindow = new LoginWindow();
	loginWindow->show();
	close();
}

void RegisterWindow::onRegisterClick()
{
}

void RegisterWindow::onRegisterResponse()
{
}

void RegisterWindow::onError()
{
}

void RegisterWindow::onCredentialsChange()
{
	ui.registerButton->setEnabled(isUsernameAndPasswordValid());
}
