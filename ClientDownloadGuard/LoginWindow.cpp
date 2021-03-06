#include <QtNetwork/QNetworkAccessManager>
#include <QTimer>


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

	ui.loginButton->setEnabled(false);

#ifdef _DEBUG	
	ui.usernameLineEdit->setText("adam997");
	ui.passwordLineEdit->setText("jp2gmd2137");
#endif

}

void LoginWindow::setUsernameAndPasswordText(QString& username, QString& password)
{
	ui.usernameLineEdit->setText(username);
	ui.passwordLineEdit->setText(password);
}

void LoginWindow::setupConnections()
{
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.loginButton, onLoginClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.quitButton, onQuitClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.registerButton, onRegisterClick());
	connect(ui.usernameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onCredentialsTextChanged()));
	connect(ui.passwordLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onCredentialsTextChanged()));
}

void LoginWindow::onLoginClick()
{
	loading->startLoading();
	ui.statusBar->showMessage("Logging...");
	QString username = ui.usernameLineEdit->text();
	QString password = ui.passwordLineEdit->text();
	reply = QSharedPointer<QNetworkReply>(
		ServerConnectionManager::serverConnectionManager->login(username, password));
	SERVER_RESPONSE_TO_THIS_CONNECTION(reply, LoginWindow::onLoginResponse, LoginWindow::onError);
	if (ui.waitForServer->isChecked())
	{
		connect(reply.get(), &QNetworkReply::errorOccurred, this, &LoginWindow::waitForServer);
	}

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
	if (state == "Success")
	{
		if (mainPanelWindow == Q_NULLPTR)
		{
			mainPanelWindow = new MainPanelWindow(value);
		}
		else
		{
			mainPanelWindow->setAuthKey(value);
			emit mainPanelWindow->becomeOnline();
		}
		mainPanelWindow->show();
		loading->stopLoading();
		close();
	}
	else
	{
		ui.statusBar->showMessage(state + ": " + value);
	}
	loading->stopLoading();
	ui.loginButton->setEnabled(areUsernameAndPasswordValid());
}
void LoginWindow::onError(QNetworkReply::NetworkError errorCode)
{
	loading->stopLoading();
	ui.statusBar->showMessage("Error: " + QString::number(errorCode));
}

bool LoginWindow::areUsernameAndPasswordValid()
{
	return usernameValidator->isValid(ui.usernameLineEdit->text()) && passwordValidator->isValid(
		ui.passwordLineEdit->text());
}

void LoginWindow::waitForServer(QNetworkReply::NetworkError errorCode)
{
	hide();
	if (mainPanelWindow == Q_NULLPTR)
	{
		mainPanelWindow = new MainPanelWindow("");
		mainPanelWindow->show();
	}
	QTimer::singleShot(5000, this, &LoginWindow::onLoginClick);
}

void LoginWindow::onCredentialsTextChanged()
{
	ui.loginButton->setEnabled(areUsernameAndPasswordValid());
}
