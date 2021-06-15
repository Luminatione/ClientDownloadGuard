#include "RegisterWindow.h"

#include "LoginWindow.h"
#include "QtMacros.h"
#include "ServerConnectionManager.h"

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
	QString username = ui.usernameLineEdit->text();
	QString password = ui.passwordLineEdit->text();
	reply = QSharedPointer<QNetworkReply>(
		ServerConnectionManager::serverConnectionManager->registerNewUser(username, password));
	connect(reply.get(), &QIODevice::readyRead, this, &RegisterWindow::onRegisterResponse);
	connect(reply.get(), &QNetworkReply::errorOccurred, this, &RegisterWindow::onError);
}

void RegisterWindow::onRegisterResponse()
{
}

void RegisterWindow::onError(QNetworkReply::NetworkError errorCode)
{
	//ui.statusBar->showMessage("Error: " + QString::number(errorCode));
}

void RegisterWindow::onCredentialsChange()
{
	ui.registerButton->setEnabled(isUsernameAndPasswordValid());
}
