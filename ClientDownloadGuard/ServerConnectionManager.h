#pragma once

#include <QString>
#include <QtNetwork/QNetworkAccessManager>

class ServerConnectionManager
{
public:
	static QSharedPointer<ServerConnectionManager> serverConnectionManager;
	
private:
	static QUrlQuery getQueryWithLoginAndPassword(QString& login, QString& password);
	
#ifdef _DEBUG
	QString hostname = "http://localhost:5000/api/";
#else
	QString hostname = "http://192.168.1.10:5000/api/";
#endif
	
	QString loginPage = "login";
	QString registerPage = "register";
	
	QSharedPointer<QNetworkAccessManager> networkAccessManager;	
	ServerConnectionManager(QObject* caller);
	
public:
	QSharedPointer<QNetworkReply> login(QString& username, QString& password);
};

