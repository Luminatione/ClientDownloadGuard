#include "ScheduleService.h"
#include <Windows.h>

ScheduleService::ScheduleService()
{
	loadSchedule();
}

bool ScheduleService::isCurrentWeekDaySelected(int days)
{
	int mask = 0b10000000;//mask has to have one more zero bcs dayOfWeek return 1 for monday and 7 for sunday
	QDate date = QDate::currentDate();
	bool result = days & (mask >> date.dayOfWeek());
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

bool ScheduleService::isCurrentTimeBetweenTimeBounds(QTime& current, QTime& begin, QTime& end)
{
	if (begin < end)
	{
		return current >= begin && current <= end;
	}
	else
	{
		return current >= begin || current <= end;
	}
}

void ScheduleService::work()
{
	while (true)
	{
		QTime currentTime = QTime::currentTime();
		for (auto& record : records)
		{
			if (record.enabled && isCurrentTimeBetweenTimeBounds(currentTime, record.begin, record.end) && isCurrentWeekDaySelected(record.days) && !ongoingSchedules.contains(&record))
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
}

void ScheduleService::loadSchedule()
{
	records.clear();
	ongoingSchedules.clear();
	scheduleRecordIO.resetFileCursor();
	while (!scheduleRecordIO.atEnd())
	{
		records.push_back(scheduleRecordIO.getNextRecord());
	}
}
