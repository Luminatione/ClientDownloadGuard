#include "AutoDetectionWorker.h"

#include <Windows.h>
void AutoDetectionWorker::loadAutoDetectedWindows()
{
	records.clear();
	autoDetectionIO.resetFileCursor();
	while (!autoDetectionIO.atEnd())
	{
		AutoDetectionRecord record = autoDetectionIO.getNextRecord();
		records.push_back(record);
	}
}

bool AutoDetectionWorker::hasConnection()
{
	return networkState != -1;
}

HWND AutoDetectionWorker::getWindowWithName(QString& windowName)
{
	return FindWindowW(nullptr, reinterpret_cast<LPCWSTR>(windowName.utf16()));
}

bool AutoDetectionWorker::isNetworkFree()
{
	return networkState == 0;
}

bool AutoDetectionWorker::networkStateShouldBeIgnored(int conflictBehaviour)
{
	return conflictBehaviour == 0;
}

bool AutoDetectionWorker::shouldNotifyUserOnConflict(int conflictBehaviour)
{
	return conflictBehaviour == 1;
}

bool AutoDetectionWorker::wantsToChangeState(int type)
{
	return type != 3;
}

void AutoDetectionWorker::work()
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
						emit onSetState(record.type, description);
					}
					else if (shouldNotifyUserOnConflict(record.conflictBehaviour))
					{
						emit onNotify(record.type, record.windowName);
					}
					checkedWindows.push_back(window);
					emit onUpdate();
				}
			}
		}
		Sleep(10000);
	}
}

void AutoDetectionWorker::setState(int _state)
{
	QMutexLocker<QMutex>locker(&mutex);
	this->networkState = _state;
}

AutoDetectionWorker::AutoDetectionWorker(QMainWindow* parent)
{
	this->parent = parent;
	loadAutoDetectedWindows();
}
