#pragma once

#include <QTime>
class ScheduleRecord
{
public:
	QString name = " ";
	bool enabled = true;
	QTime begin;
	QTime end;

	friend bool operator==(const ScheduleRecord& lhs, const ScheduleRecord& rhs)
	{
		return lhs.name == rhs.name
			&& lhs.enabled == rhs.enabled
			&& lhs.begin == rhs.begin
			&& lhs.end == rhs.end
			&& lhs.days == rhs.days
			&& lhs.repeat == rhs.repeat
			&& lhs.type == rhs.type
			&& lhs.onConflictBehaviour == rhs.onConflictBehaviour
			&& lhs.removeOnEnd == rhs.removeOnEnd;
	}

	friend bool operator!=(const ScheduleRecord& lhs, const ScheduleRecord& rhs)
	{
		return !(lhs == rhs);
	}

	int days = 0;
	bool repeat = false;
	int type = 0;
	int onConflictBehaviour = 0;
	bool removeOnEnd = false;


};
QDataStream& operator <<(QDataStream&, ScheduleRecord&);
QDataStream& operator >>(QDataStream&, ScheduleRecord&);
