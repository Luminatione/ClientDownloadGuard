#pragma once

#include <QTime>
class ScheduleRecord
{
public:
	QString name = " ";
	bool enabled = true;
	QTime begin;
	QTime end;
	int days = 0;
	bool repeat = false;
	int type = 0;
	int onConflictBehaviour = 0;
	bool removeOnEnd = false;


};
QDataStream& operator <<(QDataStream&, ScheduleRecord&);
QDataStream& operator >>(QDataStream&, ScheduleRecord&);

