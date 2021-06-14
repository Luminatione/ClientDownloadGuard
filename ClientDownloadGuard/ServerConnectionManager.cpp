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

QSharedPointer<QNetworkReply> ServerConnectionManager::login(QString& username, QString& password)
{
	QString url = hostname + loginPage + '?' + getQueryWithLoginAndPassword(username, password).query();
	
	QNetworkRequest request;
	request.setUrl(url);

	QSharedPointer<QNetworkReply> reply = QSharedPointer<QNetworkReply>(networkAccessManager->get(request));
	
	return reply;
}
