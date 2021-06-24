#pragma once
#include <QString>
#include <QVector>

#include "AutoDetectionReader.h"

class AutoDetectionWorker
{
	struct Record
	{
		QString	windowName;
		int type;
		int onConflictBehaviour;
	};
	QVector<Record> records;
	AutoDetectionReader autoDetectionReader = AutoDetectionReader();
	bool doWork = true;
public:
	AutoDetectionWorker();
	void loadAutoDetectedWindows();
	void work();
};

