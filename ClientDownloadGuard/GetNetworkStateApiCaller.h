#pragma once
#include "RESTApiCaller.h"

class GetNetworkStateApiCallerArguments
{
public:
	QString authKey;
};

class GetNetworkStateApiCaller : public RESTApiCaller<GetNetworkStateApiCallerArguments>
{
	QString getNetworkStatePage = "GetNetworkState";
	QUrlQuery getQueryWithLoginAndPassword(QString& authKey);
	QString getUrl(QString& hostname, QString& authKey);
public:
	QNetworkReply* call(QNetworkAccessManager* accessManager, QString& hostname, GetNetworkStateApiCallerArguments arguments) override;
};

