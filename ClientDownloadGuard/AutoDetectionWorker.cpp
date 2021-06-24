#include "AutoDetectionWorker.h"

#include <Windows.h>
void AutoDetectionWorker::loadAutoDetectedWindows()
{
	while (!autoDetectionReader.atEnd())
	{
		auto [windowName, type, onConflictBehaviour] = autoDetectionReader.getNextRecord();
		records.push_back({windowName, type, onConflictBehaviour});
	}
}

void AutoDetectionWorker::work()
{
	while (doWork)
	{
		//TODO: enumerating thru all windows and check if there are listed in records;
		Sleep(30000);
	}
}

AutoDetectionWorker::AutoDetectionWorker()
{
	loadAutoDetectedWindows();
}
