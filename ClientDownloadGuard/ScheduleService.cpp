#include "ScheduleService.h"

ScheduleService::ScheduleService()
{
	loadSchedule();
}

void ScheduleService::work()
{
	for(auto& record : records)
	{
		QTime currentTime = QTime::currentTime();
		if(currentTime >= record.begin && currentTime <= record.end)//TODO: correct to work with every case
		{
			
		}
	}
}

void ScheduleService::loadSchedule()
{
	scheduleRecordIO.resetFileCursor();
	while (!scheduleRecordIO.atEnd())
	{
		records.push_back(scheduleRecordIO.getNextRecord());
	}
}
