#include "ResponseReader.h"

#include <QNetworkReply>

std::tuple<QJsonValueRef, QJsonValueRef> ResponseReader::getStateAndValueJsonRefValues(QNetworkReply* reply)
{
	QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
	return std::make_tuple(document.object()[stateName], document.object()[valueName]);
}

std::tuple<QString, QString> ResponseReader::getStateAndValueQStrings(QNetworkReply* reply)
{
	QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
	return std::make_tuple(document.object()[stateName].toString(), document.object()[valueName].toString());
}
