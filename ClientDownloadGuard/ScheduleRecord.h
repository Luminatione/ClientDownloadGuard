#pragma once

#include <QTime>
class ScheduleRecord
{
public:
	bool enabled;
	int behaviour;
	QTime begin;
	QTime end;
	int days;
	int type;
	int onConflictBehaviour;
	bool removeOnEnd;


};
QDataStream& operator <<(QDataStream&, ScheduleRecord&);
QDataStream& operator >>(QDataStream&, ScheduleRecord&);

