#include "ServerConnectionManager.h"

QSharedPointer<ServerConnectionManager> ServerConnectionManager::serverConnectionManager = QSharedPointer<ServerConnectionManager>(new ServerConnectionManager());

ServerConnectionManager::ServerConnectionManager(QObject* caller = nullptr)
{
	//networkAccessManager = std::make_unique<QNetworkAccessManager>(caller);
	
}
