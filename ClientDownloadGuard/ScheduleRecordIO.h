#pragma once
#include "DataRecordIO.h"
#include "ScheduleRecord.h"

class ScheduleRecordIO : public DataRecordIO<ScheduleRecord>
{
public:
	ScheduleRecordIO();
};

