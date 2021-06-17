#include "GetNetworkStateApiCaller.h"

QString GetNetworkStateApiCaller::getUrl(QString& hostname, QString& authKey)
{
	
}

QNetworkReply* GetNetworkStateApiCaller::call(QNetworkAccessManager* accessManager, QString& hostname,
                                              GetNetworkStateApiCallerArguments arguments)
{
	QNetworkRequest request;
	request.setUrl(getUrl(hostname, arguments.authKey));
	return accessManager->get(request);
}
