#include "ResponseReader.h"

#include <QNetworkReply>

std::tuple<QJsonValueRef, QJsonValueRef> ResponseReader::GetStateAndValueJsonObjects(QNetworkReply* reply)
{
	QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
	return std::make_tuple(document.object()[stateName], document.object()[valueName]);
}
