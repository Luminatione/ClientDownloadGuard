#include "ScheduleService.h"
#include <Windows.h>

ScheduleService::ScheduleService()
{
	loadSchedule();
}

bool ScheduleService::isCurrentWeekDaySelected(ScheduleRecord& record)
{
	int mask = 0b10000000;//mask has to have one more zero bcs dayOfWeek return 1 for monday and 7 for sunday
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
	scheduleRecordIO.save();
}

void ScheduleService::work()
{
	while (true)
	{
		QTime currentTime = QTime::currentTime();
		for (auto& record : records)
		{
			if (record.enabled && currentTime >= record.begin && currentTime <= record.end && isCurrentWeekDaySelected(record) && !ongoingSchedules.contains(&record))//TODO: correct to work in every case
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
		Sleep(10000);
	}
}

void ScheduleService::loadSchedule()
{
	records.clear();
	scheduleRecordIO.resetFileCursor();
	while (!scheduleRecordIO.atEnd())
	{
		records.push_back(scheduleRecordIO.getNextRecord());
	}
}
