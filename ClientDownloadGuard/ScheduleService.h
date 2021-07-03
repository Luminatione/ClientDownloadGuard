#pragma once
#include <QMutex>
#include <QObject>

#include "ScheduleRecord.h"
#include "ScheduleRecordIO.h"
#include "Service.h"

class ScheduleService : public Service
{
	QVector<ScheduleRecord> records;
	ScheduleRecordIO scheduleRecordIO;
	QVector<ScheduleRecord*> ongoingSchedules;
public:
	ScheduleService();
	void work() override;
public slots:
	void loadSchedule();
private:
	bool isCurrentWeekDaySelected(int days);
	void saveSchedule();
	bool isCurrentTimeBetweenTimeBounds(QTime& current, QTime& begin, QTime& end);
};

