#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <qnetworkreply.h>
#include <tuple>

class ResponseReader
{
	static inline QString stateName = "state";
	static inline QString valueName = "value";
public:
	static std::tuple<QJsonValue, QJsonValue> getStateAndValueJsonRefValues(QNetworkReply* reply);
	static std::tuple<QString, QString> getStateAndValueQStrings(QNetworkReply* reply);
};

