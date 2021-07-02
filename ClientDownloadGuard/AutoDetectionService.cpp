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

bool AutoDetectionService::isNetworkFree()
{
	return networkState == 0;
}

bool AutoDetectionService::networkStateShouldBeIgnored(int conflictBehaviour)
{
	return conflictBehaviour == 0;
}

bool AutoDetectionService::shouldNotifyUserOnConflict(int conflictBehaviour)
{
	return conflictBehaviour == 1;
}

bool AutoDetectionService::wantsToChangeState(int type)
{
	return type != 3;
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
						emit setState(record.type, description);
					}
					else if (shouldNotifyUserOnConflict(record.conflictBehaviour))
					{
						emit notify(record.type, record.windowName);
					}
					checkedWindows.push_back(window);
					emit update();
				}
			}
		}
		Sleep(10000);
	}
}

void AutoDetectionService::setState(int _state)
{
	QMutexLocker<QMutex>locker(&mutex);
	this->networkState = _state;
}

AutoDetectionService::AutoDetectionService()
{
	loadAutoDetectedWindows();
}
