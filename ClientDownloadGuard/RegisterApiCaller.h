#pragma once
#include "RESTApiCaller.h"

struct RegisterApiCallerArguments
{
	QString username;
	QString password;
};
class RegisterApiCaller : public RESTApiCaller<RegisterApiCallerArguments>
{
	QString registerPage = "register";
	QUrlQuery getQueryWithLoginAndPassword(const QString& username, const QString& password);
	QString getRegisterUrl(QString& hostname, QString& username, QString& password);
	QNetworkReply* call(QNetworkAccessManager* accessManager, QString& hostname, RegisterApiCallerArguments arguments) override;
};

