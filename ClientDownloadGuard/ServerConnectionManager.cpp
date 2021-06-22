#include "ServerConnectionManager.h"


#include <QNetworkReply>
#include <QUrlQuery>
#include <QApplication>


QSharedPointer<ServerConnectionManager> ServerConnectionManager::serverConnectionManager = QSharedPointer<ServerConnectionManager>(new ServerConnectionManager(nullptr));

ServerConnectionManager::ServerConnectionManager(QObject* caller = nullptr)
{
	networkAccessManager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager());
	networkAccessManager->setTransferTimeout(7000);

	//QString path = QApplication::applicationDirPath() + "/config.ini";
	//QSettings settings = QSettings(path, QSettings::IniFormat);
	//QString a = settings.fileName();
	//settings.setValue("hostname", hostname);
	//settings.sync();
	//hostname = settings.value("hostname").toString();
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
