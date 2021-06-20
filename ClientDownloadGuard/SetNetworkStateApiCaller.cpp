#include <QUrlQuery>

#include "SetNetworkStateApiCaller.h"

QUrlQuery SetNetworkStateApiCaller::getQuery(QString& authKey, int type, QString& description)
{
	QUrlQuery query;
	query.addQueryItem("authKey", authKey);
	query.addQueryItem("type", QString::number(type));
	query.addQueryItem("description", description);
	return query;
}

QString SetNetworkStateApiCaller::getUrl(QString& hostname, QString& authKey, int type, QString& description)
{
	return hostname + setNetworkStatePage + '?' + getQuery(authKey, type, description).query();
}

QNetworkReply* SetNetworkStateApiCaller::call(QNetworkAccessManager* accessManager, QString& hostname,
                                              SetNetworkStateApiCallerArguments arguments)
{
	QNetworkRequest request;
	QString url = getUrl(hostname, arguments.authKey, arguments.type, arguments.description);
	request.setUrl(url);
	return accessManager->get(request);
}
