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
	QString getUrl(QString& hostname, QString& authKey);
	QNetworkReply* call(QNetworkAccessManager* accessManager, QString& hostname, GetNetworkStateApiCallerArguments arguments) override;
};

