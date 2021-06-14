#include <QtNetwork/QNetworkAccessManager>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>


#include "LoginWindow.h"
#include "QtMacros.h"
#include "PasswordValidator.h"
#include "UsernameValidator.h"
#include "ServerConnectionManager.h"


LoginWindow::LoginWindow(QWidget* parent)
	: QMainWindow(parent)
{
	usernameValidator = QSharedPointer<UsernameValidator>(new UsernameValidator());
	passwordValidator = QSharedPointer<PasswordValidator>(new PasswordValidator());
	networkAccessManager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager(this));
	ui.setupUi(this);
	setupConnections();

	ui.LoginButton->setEnabled(false);
}

void LoginWindow::setupConnections()
{
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.LoginButton, onLoginClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.QuitButton, onQuitClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.RegisterButton, onRegisterClick());
	connect(ui.UsernameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onCredentialsTextChanged()));
	connect(ui.PasswordLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onCredentialsTextChanged()));
}

void LoginWindow::onLoginClick()
{
	ui.statusBar->showMessage("Logging...");
	
	reply = ServerConnectionManager::serverConnectionManager->login(ui.UsernameLineEdit->text(), ui.PasswordLineEdit->text());	
	connect(reply.get(), &QIODevice::readyRead, this, &LoginWindow::onLoginResponse);
	connect(reply.get(), &QNetworkReply::errorOccurred, this, &LoginWindow::onError);

}

void LoginWindow::onQuitClick()
{
	QApplication::quit();
}

void LoginWindow::onRegisterClick()
{

}

void LoginWindow::onLoginResponse()
{
	QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
	QString state = document.object()["state"].toString();
	QString value = document.object()["value"].toString();
	if(state == "Failure")
	{
		ui.statusBar->showMessage(state + ": " + value);
	}
}
void LoginWindow::onError(QNetworkReply::NetworkError code)
{
	ui.statusBar->showMessage("Error: " + QString::number(code));
}

void LoginWindow::onCredentialsTextChanged()
{
	isLoginValid = usernameValidator->isValid(ui.UsernameLineEdit->text());
	isPasswordValid = passwordValidator->isValid(ui.PasswordLineEdit->text());
	ui.LoginButton->setEnabled(isLoginValid && isPasswordValid);
}
