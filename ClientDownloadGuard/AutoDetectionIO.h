#pragma once
#include "AutoDetectionRecord.h"
#include "DataRecordIO.h"

class AutoDetectionIO : public DataRecordIO<AutoDetectionRecord>
{
public:
	AutoDetectionIO();
};

