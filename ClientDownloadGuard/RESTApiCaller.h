#pragma once
#include <QString>
#include <QNetworkReply>
#include <QSharedPointer>

class RESTApiCaller
{
public:
	virtual ~RESTApiCaller() = default;
	virtual QSharedPointer<QNetworkReply> call() = 0;
	virtual QSharedPointer<QNetworkReply> call(QString arg0) = 0;
	virtual QSharedPointer<QNetworkReply> call(QString arg0, QString arg1) = 0;
	virtual QSharedPointer<QNetworkReply> call(QString arg0, QString arg1, QString arg2) = 0;
};

