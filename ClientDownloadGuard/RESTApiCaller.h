#pragma once
#include <QString>
#include <QNetworkReply>
#include <QSharedPointer>
#include <QStringList>
#include <QMap>

template <typename T> class RESTApiCaller
{
public:
	virtual QNetworkReply* call(QNetworkAccessManager* accessManager, QString& hostname, T arguments) = 0;
	virtual ~RESTApiCaller() = default;
};

