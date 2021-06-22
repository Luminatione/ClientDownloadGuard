#include "ServerConnectionManager.h"


#include <QNetworkReply>
#include <QUrlQuery>
#include <QApplication>


QSharedPointer<ServerConnectionManager> ServerConnectionManager::serverConnectionManager = QSharedPointer<ServerConnectionManager>(new ServerConnectionManager(nullptr));

ServerConnectionManager::ServerConnectionManager(QObject* caller = nullptr)
{
	networkAccessManager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager());
	networkAccessManager->setTransferTimeout(7000);
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

QNetworkReply* ServerConnectionManager::setNetworkState(QString& authKey, int type, QString& description)
{
	return setNetworkStateApiCaller->call(networkAccessManager.get(), hostname, { authKey,  description, type });
}

void ServerConnectionManager::setHostname(QString hostname)
{
	this->hostname = hostname;
}
