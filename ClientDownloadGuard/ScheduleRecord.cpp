#include "ScheduleRecord.h"

QDataStream& operator<<(QDataStream& stream, ScheduleRecord& record)
{
	stream << record.name << record.enabled << record.begin << record.end << record.days << record.repeat << record.type << record.onConflictBehaviour << record.removeOnEnd;
	return stream;
}

QDataStream& operator>>(QDataStream& stream, ScheduleRecord& record)
{
	stream >> record.name >> record.enabled >> record.begin >> record.end >> record.days >> record.repeat >> record.type >> record.onConflictBehaviour >> record.removeOnEnd;
	return stream;
}