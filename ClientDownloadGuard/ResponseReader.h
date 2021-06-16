#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <qnetworkreply.h>
#include <tuple>

class ResponseReader
{
	QString stateName = "state";
	QString valueName = "value";
public:
	std::tuple<QJsonValueRef, QJsonValueRef> GetStateAndValueJsonObjects(QNetworkReply* reply);
};

