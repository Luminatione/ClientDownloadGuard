#pragma once

#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <memory>

class ServerConnectionManager
{
	template <typename T> struct ConnectionArgument
	{
		QString name;
		T value;
	};
	QString hostname;
	std::unique_ptr<QNetworkAccessManager> networkAccessManager;
	ServerConnectionManager(QObject* caller);
	QNetworkAccessManager* get()
	{
		
		return networkAccessManager.get();
	}
};

