#include "LoginWindow.h"
#include "QtMacros.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>

#include "UsernameValidator.h"


LoginWindow::LoginWindow(QWidget* parent)
	: QMainWindow(parent)
{
	usernameValidator = QSharedPointer<UsernameValidator>();
	networkAccessManager = QSharedPointer<QNetworkAccessManager>();
	ui.setupUi(this);
	setupConnections();
}

void LoginWindow::setupConnections()
{
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.LoginButton, onLoginClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.QuitButton, onQuitClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.RegisterButton, onRegisterClick());
	connect(ui.UsernameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onUsernameTextChanged()));
	connect(ui.PasswordLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onPasswordTextChanged()));
}

void LoginWindow::onLoginClick()
{
	ui.statusBar->showMessage("Logging...");
	QNetworkRequest request;
	QUrlQuery query;
	query.addQueryItem("login",  ui.UsernameLineEdit->text() );
	query.addQueryItem("password",  ui.PasswordLineEdit->text() );
	QString url = hostname + loginPage + '?' + query.query();
	request.setUrl(url);
	reply = QSharedPointer<QNetworkReply>(networkAccessManager->get(request));
	//connect(reply, SIGNAL(finished()), this, SLOT(onLoginResponse));
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

void LoginWindow::onUsernameTextChanged(QString currentText)
{
	usernameValidator->isValid(currentText);
}

void LoginWindow::onPasswordTextChanged(QString currentText)
{
	
}
