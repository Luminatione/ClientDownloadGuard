#include "LoginApiCaller.h"

#include <QUrlQuery>

QUrlQuery LoginApiCaller::getQueryWithLoginAndPassword(QString login, QString password)
{
	QUrlQuery query;
	query.addQueryItem("login", login);
	query.addQueryItem("password", password);
	return query;
}

const QString LoginApiCaller::getLoginUrl(QString& hostname, QString& username, QString& password)
{
	return hostname + loginPage + '?' + getQueryWithLoginAndPassword(username, password).query();
}

QNetworkReply* LoginApiCaller::call(QNetworkAccessManager* accessManager, QString& hostname, LoginApiCallerArguments callArguments)
{
	QNetworkRequest request;
	request.setUrl(getLoginUrl(hostname, callArguments.username, callArguments.password));
	QNetworkReply* reply = accessManager->get(request);
	return reply;
}
