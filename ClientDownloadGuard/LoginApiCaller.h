#pragma once
#include "RESTApiCaller.h"

struct LoginApiCallerArguments
{
	QString& username;
	QString& password;
};

class LoginApiCaller : public RESTApiCaller<LoginApiCallerArguments>
{
	QString loginPage = "login";

	static QUrlQuery getQueryWithLoginAndPassword(QString login, QString password);
	const QString getLoginUrl(QString& hostname, QString& username, QString& password);
public:
	QNetworkReply* call(QNetworkAccessManager* accessManager, QString& hostname, LoginApiCallerArguments callArguments) override;
};

