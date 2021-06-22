#pragma once

#include <QString>
#include <QtNetwork/QNetworkAccessManager>

#include "GetNetworkStateApiCaller.h"
#include "RESTApiCaller.h"
#include "LoginApiCaller.h"
#include "RegisterApiCaller.h"
#include "SetNetworkStateApiCaller.h"
#include "Settings.h"

class ServerConnectionManager
{

public:
	static QSharedPointer<ServerConnectionManager> serverConnectionManager;
	
private:
	ServerConnectionManager(QObject* caller);

	QSharedPointer<QNetworkAccessManager> networkAccessManager;	
#ifdef _DEBUG
	QString hostname = "http://localhost:5000/api/";
#else
	QString hostname = "http://192.168.1.110:5000/api/";
#endif
	
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
};

