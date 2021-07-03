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

bool AutoDetectionService::hasConnection()
{
	return networkState != -1;
}

HWND AutoDetectionService::getWindowWithName(QString& windowName)
{
	return FindWindowW(nullptr, reinterpret_cast<LPCWSTR>(windowName.utf16()));
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
						QString text = "Conflict occurred during network state setting for" + record.windowName + ". Do you want to override current state?";
						emit notify(record.type, title, text);
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
