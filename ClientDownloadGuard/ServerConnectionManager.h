#pragma once

#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <memory>

class ServerConnectionManager
{
	QString hostname;
	std::unique_ptr<QNetworkAccessManager> networkAccessManager;
	ServerConnectionManager(QObject* caller)
	{
		networkAccessManager = std::make_unique<QNetworkAccessManager>(caller);
	}

};

