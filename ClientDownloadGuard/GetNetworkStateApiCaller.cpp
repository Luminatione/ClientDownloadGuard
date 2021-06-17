#include "GetNetworkStateApiCaller.h"
#include <QUrlQuery>

QUrlQuery GetNetworkStateApiCaller::getQueryWithLoginAndPassword(QString& authKey)
{
	QUrlQuery query;
	query.addQueryItem("authKey", authKey);
	return query;
}

QString GetNetworkStateApiCaller::getUrl(QString& hostname, QString& authKey)
{
	return hostname + getNetworkStatePage + '?' + getQueryWithLoginAndPassword(authKey).query();
}

QNetworkReply* GetNetworkStateApiCaller::call(QNetworkAccessManager* accessManager, QString& hostname,
                                              GetNetworkStateApiCallerArguments arguments)
{
	QNetworkRequest request;
	request.setUrl(getUrl(hostname, arguments.authKey));
	return accessManager->get(request);
}
