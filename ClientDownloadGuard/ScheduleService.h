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

public:
	ScheduleService();
	void work() override;
private slots:
	void loadSchedule();
};

