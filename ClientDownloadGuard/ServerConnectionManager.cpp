#include "ServerConnectionManager.h"
#include "DefaultSettings.h"

#include <QSettings>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QApplication>


ServerConnectionManager* ServerConnectionManager::serverConnectionManager = new ServerConnectionManager(nullptr);

ServerConnectionManager::ServerConnectionManager(QObject* caller = nullptr)
{
	networkAccessManager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager());	
	networkAccessManager->setTransferTimeout(7000);
}

QString ServerConnectionManager::getApiConnectionUrl()
{
	QSettings settings = QSettings();
	QString a = settings.fileName();
	QString hostname = settings.value("hostname", DefaultSettings::settings->defaultHostname).toString();
	QString port = settings.value("port", DefaultSettings::settings->defaultPort).toString();
	QString protocol = settings.value("protocol", DefaultSettings::settings->defaultProtocol).toString();
	return protocol + hostname + ":" + port + "/api/";
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

void ServerConnectionManager::syncWithSettings()
{
	hostname = getApiConnectionUrl();
}
