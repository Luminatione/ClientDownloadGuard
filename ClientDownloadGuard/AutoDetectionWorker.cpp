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

void AutoDetectionWorker::work()
{
	MainPanelWindow* mainPanelWindow = dynamic_cast<MainPanelWindow*>(parent);
	while (doWork)
	{
		if (networkState != -1)
		{
			for (auto record : records)
			{
				HWND window = FindWindowW(nullptr, reinterpret_cast<LPCWSTR>(record.windowName.utf16()));
				if (window && !resolvedWindows.contains(window))
				{
					if (networkState == 0 || record.onConflictBehaviour == 0)
					{
						QString description = "I'm using " + record.windowName;
						mutex.lock();
						mainPanelWindow->setState(record.type, description);
						mutex.unlock();
					}
					else if (record.onConflictBehaviour == 1)
					{
						emit onNotify(record.type, record.windowName);
					}
					emit onUpdate();
					resolvedWindows.push_back(window);
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
