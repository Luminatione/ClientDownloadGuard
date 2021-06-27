#include "AutoDetectionWorker.h"
#include "MainPanelWindow.h"

#include <QMessageBox>
#include <Windows.h>
void AutoDetectionWorker::loadAutoDetectedWindows()
{
	records.clear();
	autoDetectionReader.resetFileCursor();
	while (!autoDetectionReader.atEnd())
	{
		auto [windowName, type, onConflictBehaviour] = autoDetectionReader.getNextRecord();
		records.push_back({ windowName, type, onConflictBehaviour });
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
	MainPanelWindow* mainPanelWindow = dynamic_cast<MainPanelWindow*>(parent);
	while (doWork)
	{
		if (hasConnection())
		{
			for (auto record : records)
			{
				HWND window = getWindowWithName(record.windowName);
				if (window && !checkedWindows.contains(window) && wantsToChangeState(record.type))
				{
					if (isNetworkFree() || networkStateShouldBeIgnored(record.onConflictBehaviour))
					{
						QString description = "I'm using " + record.windowName;
						emit onSetState(record.type, description);
					}
					else if (shouldNotifyUserOnConflict(record.onConflictBehaviour))
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
