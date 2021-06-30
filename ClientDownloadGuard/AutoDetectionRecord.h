#pragma once
#include <QString>
#include <QDataStream>

class AutoDetectionRecord
{
public:
	QString windowName = " ";
	int type = 0;
	int conflictBehaviour = 0;
};
QDataStream& operator<<(QDataStream& dataStream, AutoDetectionRecord& autoDetectionRecord);
QDataStream& operator>>(QDataStream& dataStream, AutoDetectionRecord& autoDetectionRecord);
