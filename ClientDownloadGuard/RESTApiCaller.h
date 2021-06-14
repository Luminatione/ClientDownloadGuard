#pragma once

#include <QNetworkReply>

/**
 * \brief 
 * \tparam T Container for custom arguments in call() function
 */
template <typename T> class RESTApiCaller
{
public:
	virtual QNetworkReply* call(QNetworkAccessManager* accessManager, QString& hostname, T arguments) = 0;
	virtual ~RESTApiCaller() = default;
};

