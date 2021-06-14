#pragma once

#include <QString>
#include <QtNetwork/QNetworkAccessManager>

#include "RESTApiCaller.h"
#include "LoginApiCaller.h"

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
	QString hostname = "http://192.168.1.10:5000/api/";
#endif
	QSharedPointer<RESTApiCaller<LoginApiCallerArguments>> loginApiCaller = QSharedPointer<LoginApiCaller>(new LoginApiCaller());
public:
	QNetworkReply* login(QString& username, QString& password);
};

