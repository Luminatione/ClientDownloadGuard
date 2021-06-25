#include "AutoDetectionWorker.h"


#include <QMessageBox>
#include <Windows.h>
void AutoDetectionWorker::loadAutoDetectedWindows()
{
	while (!autoDetectionReader.atEnd())
	{
		auto [windowName, type, onConflictBehaviour] = autoDetectionReader.getNextRecord();
		records.push_back({ windowName, type, onConflictBehaviour });
	}
}

void AutoDetectionWorker::work()
{
	while (doWork)
	{
		//TODO: enumerating thru all windows and check if there are listed in records;
		for (auto& record : records)
		{
			HWND window = FindWindowW(nullptr, reinterpret_cast<LPCWSTR>(record.windowName.utf16()));
			if(window)
			{
				if(networkState == 0 || networkState == -1)
				{
					QString description = "I'm using " + record.windowName;
					mutex.lock();
					//parent->setState(record.type, description);
					mutex.unlock();
				}
				else
				{
					QMessageBox::question(nullptr, "aaa", "bbbb");
				}
			}
		}
		Sleep(30000);
	}
}

void AutoDetectionWorker::setState(int _state)
{
	QMutexLocker<QMutex>locker(&mutex);
	this->networkState = static_cast<state>(_state);
}

AutoDetectionWorker::AutoDetectionWorker(QMainWindow* parent)
{
	//this->parent = parent;
	loadAutoDetectedWindows();
}
