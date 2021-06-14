#include "ServerConnectionManager.h"


#include <QNetworkReply>
#include <QUrlQuery>

QSharedPointer<ServerConnectionManager> ServerConnectionManager::serverConnectionManager = QSharedPointer<ServerConnectionManager>(new ServerConnectionManager(nullptr));

ServerConnectionManager::ServerConnectionManager(QObject* caller = nullptr)
{
	networkAccessManager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager());
}

QSharedPointer<QNetworkReply> ServerConnectionManager::login(QString& username, QString& password)
{	
	QNetworkRequest request;
	request.setUrl(getLoginUrl(username, password));
	QSharedPointer<QNetworkReply> reply = QSharedPointer<QNetworkReply>(networkAccessManager->get(request));	
	return reply;
}
