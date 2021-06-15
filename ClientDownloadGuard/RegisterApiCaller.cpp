#include <QUrlQuery>

#include "RegisterApiCaller.h"

QUrlQuery RegisterApiCaller::getQueryWithLoginAndPassword(const QString& username, const QString& password)
{
	QUrlQuery query;
	query.addQueryItem("login", username);
	query.addQueryItem("password", password);
	return query;
}

QString RegisterApiCaller::getRegisterUrl(QString& hostname, QString& username, QString& password)
{
	return hostname + registerPage + '?' + getQueryWithLoginAndPassword(username, password).query();
}

QNetworkReply* RegisterApiCaller::call(QNetworkAccessManager* accessManager, QString& hostname,
                                       RegisterApiCallerArguments arguments)
{
	QNetworkRequest request;
	request.setUrl(getRegisterUrl(hostname, arguments.username, arguments.password));
	return accessManager->get(request);
}
