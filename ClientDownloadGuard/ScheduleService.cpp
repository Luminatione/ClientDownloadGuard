#include "ScheduleService.h"
#include <Windows.h>

ScheduleService::ScheduleService()
{
	loadSchedule();
}

bool ScheduleService::isCurrentWeekDaySelected(ScheduleRecord& record)
{
	int mask = 0b10000000;
	QDate date = QDate::currentDate();
	bool result = record.days & (mask >> date.dayOfWeek());
	return result;
}

void ScheduleService::saveSchedule()
{
	scheduleRecordIO.truncate();
	scheduleRecordIO.resetFileCursor();
	for (auto& record : records)
	{
		scheduleRecordIO.saveRecord(record);
	}
}

void ScheduleService::work()
{
	QTime currentTime = QTime::currentTime();
	QVector<ScheduleRecord*> currentSchedule;
	for (auto& record : records)
	{
		if (record.enabled && currentTime >= record.begin && currentTime <= record.end && isCurrentWeekDaySelected(record) && !ongoingSchedules.contains(record))//TODO: correct to work in every case
		{
			ongoingSchedules.push_back(&record);
			if (isNetworkFree() || networkStateShouldBeIgnored(record.onConflictBehaviour))
			{
				QString description = "Scheduled network state from " + record.begin.toString() + " to " + record.end.toString();
				emit updateNetworkState(record.type, description);
			}
			else if (shouldNotifyUserOnConflict(record.onConflictBehaviour))
			{
				QString title = "Conflict";
				QString description = "Conflict occurred during network state setting. Do you want to override current state?";
				emit notify(record.type, title, description);
			}
			emit refresh();
		}
	}
	for (auto& record : ongoingSchedules)
	{
		if (currentTime < record->begin && currentTime > record->end)
		{
			ongoingSchedules.removeOne(record);
			if (record->removeOnEnd)
			{
				records.removeOne(*record);
			}
			else
			{
				record->enabled = record->repeat;
			}
		}
	}
	saveSchedule();
	Sleep(1000);
}

void ScheduleService::loadSchedule()
{
	scheduleRecordIO.resetFileCursor();
	while (!scheduleRecordIO.atEnd())
	{
		records.push_back(scheduleRecordIO.getNextRecord());
	}
}
