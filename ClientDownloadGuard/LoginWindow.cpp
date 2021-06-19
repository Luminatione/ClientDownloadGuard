#include <QtNetwork/QNetworkAccessManager>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>


#include "LoginWindow.h"
#include "QtMacros.h"
#include "PasswordValidator.h"
#include "UsernameValidator.h"
#include "ServerConnectionManager.h"
#include "RegisterWindow.h"
#include "LoadingUtility.h"
#include "MainPanelWindow.h"
#include "ResponseReader.h"


LoginWindow::LoginWindow(QWidget* parent)
	: QMainWindow(parent)
{
	usernameValidator = QSharedPointer<UsernameValidator>(new UsernameValidator());
	passwordValidator = QSharedPointer<PasswordValidator>(new PasswordValidator());

	ui.setupUi(this);

	setupConnections();

	ui.LoginButton->setEnabled(false);

	MainPanelWindow* mainPanelWindow = new MainPanelWindow();
	mainPanelWindow->show();
}

void LoginWindow::setUsernameAndPasswordText(QString& username, QString& password)
{
	ui.UsernameLineEdit->setText(username);
	ui.PasswordLineEdit->setText(password);
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
	loading->startLoading();
	ui.statusBar->showMessage("Logging...");
	QString username = ui.UsernameLineEdit->text();
	QString password = ui.PasswordLineEdit->text();
	reply = QSharedPointer<QNetworkReply>(
		ServerConnectionManager::serverConnectionManager->login(username, password));
	SERVER_RESPONSE_TO_THIS_CONNECTION(reply, LoginWindow::onLoginResponse, LoginWindow::onError);

}

void LoginWindow::onQuitClick()
{
	QApplication::quit();
}

void LoginWindow::onRegisterClick()
{
	QWidget* registerWindow = new RegisterWindow();
	registerWindow->show();
	close();
}

void LoginWindow::onLoginResponse()
{
	auto [state, value] = ResponseReader::getStateAndValueQStrings(reply.get());
	ui.statusBar->showMessage(state + ": " + value);
	loading->stopLoading();
	
}
void LoginWindow::onError(QNetworkReply::NetworkError errorCode)
{
	ui.statusBar->showMessage("Error: " + QString::number(errorCode));
}

bool LoginWindow::isUsernameAndPasswordValid()
{
	return usernameValidator->isValid(ui.UsernameLineEdit->text()) && passwordValidator->isValid(
		ui.PasswordLineEdit->text());
}

void LoginWindow::onCredentialsTextChanged()
{
	ui.LoginButton->setEnabled(isUsernameAndPasswordValid());
}
