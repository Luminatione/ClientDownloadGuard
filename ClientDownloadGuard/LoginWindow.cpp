#include "LoginWindow.h"
#include "QtMacros.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>


LoginWindow::LoginWindow(QWidget* parent)
	: QMainWindow(parent)
{
	networkAccessManager = new QNetworkAccessManager(this);
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
	QNetworkRequest request;
	QUrlQuery query;
	query.addQueryItem("login",  ui.UsernameLineEdit->text() );
	query.addQueryItem("password",  ui.PasswordLineEdit->text() );
	QString url = hostname + loginPage + '?' + query.query();
	request.setUrl(url);
	reply = networkAccessManager->get(request);
	//connect(reply, SIGNAL(finished()), this, SLOT(onLoginResponse));
	connect(reply, &QIODevice::readyRead, this, &LoginWindow::onLoginResponse);
	connect(reply, &QNetworkReply::errorOccurred, this, &LoginWindow::onError);

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
	
	QString result;
}
