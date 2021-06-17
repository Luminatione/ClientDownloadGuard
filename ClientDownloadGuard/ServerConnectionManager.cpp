#include "ServerConnectionManager.h"


#include <QNetworkReply>
#include <QUrlQuery>

QSharedPointer<ServerConnectionManager> ServerConnectionManager::serverConnectionManager = QSharedPointer<ServerConnectionManager>(new ServerConnectionManager(nullptr));

ServerConnectionManager::ServerConnectionManager(QObject* caller = nullptr)
{
	networkAccessManager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager());
}

QNetworkReply* ServerConnectionManager::login(QString& username, QString& password)
{
	return loginApiCaller->call(networkAccessManager.get(), hostname, { username, password });
}

QNetworkReply* ServerConnectionManager::registerNewUser(QString& username, QString& password)
{
	return registerApiCaller->call(networkAccessManager.get(), hostname, { username, password });
}

QNetworkReply* ServerConnectionManager::getNetworkState(QString& authKey)
{
	return getNetworkStateApiCaller->call(networkAccessManager.get(), hostname, { authKey });
}
