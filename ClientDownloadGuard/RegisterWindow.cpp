#include <QJsonObject>
#include <QJsonDocument>

#include "RegisterWindow.h"
#include "LoginWindow.h"
#include "PasswordValidator.h"
#include "QtMacros.h"
#include "ResponseReader.h"
#include "ServerConnectionManager.h"
#include "UsernameValidator.h"

RegisterWindow::RegisterWindow(QWidget* parent) : QMainWindow(parent)
{
	usernameValidator = QSharedPointer<Validator>(new UsernameValidator());
	passwordValidator = QSharedPointer<Validator>(new PasswordValidator());
	
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
	ui.statusbar->showMessage("Processing...");
	QString username = ui.usernameLineEdit->text();
	QString password = ui.passwordLineEdit->text();
	reply = QSharedPointer<QNetworkReply>(
		ServerConnectionManager::serverConnectionManager->registerNewUser(username, password));
	SERVER_RESPONSE_TO_THIS_CONNECTION(reply, RegisterWindow::onRegisterResponse, RegisterWindow::onError);
}

void RegisterWindow::onRegisterResponse()
{
	auto [state, value] = ResponseReader::getStateAndValueQStrings(reply.get());
	ui.statusbar->showMessage(state + ": " + value);
	if(state == "Success")
	{
		LoginWindow* loginWindow = new LoginWindow();
		QString username = ui.usernameLineEdit->text();
		QString password = ui.passwordLineEdit->text();
		loginWindow->setUsernameAndPasswordText(username, password);
		loginWindow->show();
		close();
	}
}

void RegisterWindow::onError(QNetworkReply::NetworkError errorCode)
{
	ui.statusbar->showMessage("Error: " + QString::number(errorCode));
}

void RegisterWindow::onCredentialsTextChanged()
{
	ui.registerButton->setEnabled(isUsernameAndPasswordValid());
}