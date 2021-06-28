#include "ScheduleRecord.h"

QDataStream& operator<<(QDataStream& stream, ScheduleRecord& record)
{
	stream << record.name << record.enabled << record.behaviour << record.begin << record.end << record.days << record.type << record.onConflictBehaviour << record.removeOnEnd;
	return stream;
}

QDataStream& operator>>(QDataStream& stream, ScheduleRecord& record)
{
	stream >> record.name >> record.enabled >> record.behaviour >> record.begin >> record.end >> record.days >> record.type >> record.onConflictBehaviour >> record.removeOnEnd;
	return stream;
}
