#include "AutoDetectionService.h"

#include <Windows.h>
void AutoDetectionService::loadAutoDetectedWindows()
{
	records.clear();
	autoDetectionIO.resetFileCursor();
	while (!autoDetectionIO.atEnd())
	{
		AutoDetectionRecord record = autoDetectionIO.getNextRecord();
		records.push_back(record);
	}
}
void AutoDetectionService::work()
{
	while (doWork)
	{
		if (hasConnection())
		{
			for (auto record : records)
			{
				HWND window = getWindowWithName(record.windowName);
				if (window && !checkedWindows.contains(window) && wantsToChangeState(record.type))
				{
					if (isNetworkFree() || networkStateShouldBeIgnored(record.conflictBehaviour))
					{
						QString description = "I'm using " + record.windowName;
						emit updateNetworkState(record.type, description);
					}
					else if (shouldNotifyUserOnConflict(record.conflictBehaviour))
					{
						QString title = "Conflict";
						QString description = "Conflict occurred during network state setting for" + record.windowName + ". Do you want to override current state?";
						emit notify(record.type, title, description);
					}
					checkedWindows.push_back(window);
					emit refresh();
				}
			}
		}
		Sleep(10000);
	}
}
AutoDetectionService::AutoDetectionService()
{
	loadAutoDetectedWindows();
}
