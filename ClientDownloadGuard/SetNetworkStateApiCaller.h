#pragma once
#include "RESTApiCaller.h"

class SetNetworkStateApiCallerArguments
{
public:
	QString authKey;
	QString description;
	int type;
};


class SetNetworkStateApiCaller : public RESTApiCaller<SetNetworkStateApiCallerArguments>
{
	QString setNetworkStatePage = "SetNetworkState";
	QUrlQuery getQuery(QString& authKey, int type, QString& description);
	QString getUrl(QString& hostname, QString& authKey, int type, QString& description);
	QNetworkReply* call(QNetworkAccessManager* accessManager, QString& hostname, SetNetworkStateApiCallerArguments arguments) override;
};

