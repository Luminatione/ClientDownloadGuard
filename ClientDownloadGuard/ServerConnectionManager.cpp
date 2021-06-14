#include "ServerConnectionManager.h"


#include <QNetworkReply>
#include <QUrlQuery>

QSharedPointer<ServerConnectionManager> ServerConnectionManager::serverConnectionManager = QSharedPointer<ServerConnectionManager>(new ServerConnectionManager(nullptr));

ServerConnectionManager::ServerConnectionManager(QObject* caller = nullptr)
{
	networkAccessManager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager());
}

QUrlQuery ServerConnectionManager::getQueryWithLoginAndPassword(QString& login, QString& password)
{
	QUrlQuery query;
	query.addQueryItem("login", login);
	query.addQueryItem("password", password);
	return query;
}

const QString ServerConnectionManager::getLoginUrl(QString& username, QString& password)
{
	return hostname + loginPage + '?' + getQueryWithLoginAndPassword(username, password).query();
}

QSharedPointer<QNetworkReply> ServerConnectionManager::login(QString& username, QString& password)
{	
	QNetworkRequest request;
	request.setUrl(getLoginUrl(username, password));
	QSharedPointer<QNetworkReply> reply = QSharedPointer<QNetworkReply>(networkAccessManager->get(request));	
	return reply;
}
