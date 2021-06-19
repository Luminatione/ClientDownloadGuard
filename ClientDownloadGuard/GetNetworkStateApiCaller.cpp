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
	QString url = getUrl(hostname, arguments.authKey);
	request.setUrl(url);
	return accessManager->get(request);
}
