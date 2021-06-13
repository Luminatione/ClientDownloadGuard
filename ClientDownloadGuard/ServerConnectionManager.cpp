#include "ServerConnectionManager.h"

ServerConnectionManager::ServerConnectionManager(QObject* caller)
{
	networkAccessManager = std::make_unique<QNetworkAccessManager>(caller);
	
}
