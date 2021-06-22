#pragma once

#include <QMainWindow>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>

#include "GetNetworkStateApiCaller.h"
#include "RESTApiCaller.h"
#include "LoginApiCaller.h"
#include "RegisterApiCaller.h"
#include "SetNetworkStateApiCaller.h"
#include "DefaultSettings.h"

class ServerConnectionManager : public QObject
{
	Q_OBJECT
public:
	static ServerConnectionManager* serverConnectionManager;
	
private:
	ServerConnectionManager(QObject* caller);

	QString getApiConnectionUrl();
	QSharedPointer<QNetworkAccessManager> networkAccessManager;
	
	QString hostname;
	
	QSharedPointer<RESTApiCaller<LoginApiCallerArguments>> loginApiCaller = QSharedPointer<LoginApiCaller>(new LoginApiCaller());
	QSharedPointer<RESTApiCaller<RegisterApiCallerArguments>> registerApiCaller = QSharedPointer<RegisterApiCaller>(new RegisterApiCaller());
	QSharedPointer<RESTApiCaller<GetNetworkStateApiCallerArguments>> getNetworkStateApiCaller = QSharedPointer<GetNetworkStateApiCaller>(new GetNetworkStateApiCaller());
	QSharedPointer<RESTApiCaller<SetNetworkStateApiCallerArguments>> setNetworkStateApiCaller = QSharedPointer<SetNetworkStateApiCaller>(new SetNetworkStateApiCaller());
public:
	QNetworkReply* login(QString& username, QString& password);
	QNetworkReply* registerNewUser(QString& username, QString& password);
	QNetworkReply* getNetworkState(QString& authKey);
	QNetworkReply* setNetworkState(QString& authKey, int type, QString& description);
	void setHostname(QString hostname);
	void syncWithSettings();
};

