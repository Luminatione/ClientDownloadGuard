#pragma once
#include <QMainWindow>
#include <QString>
#include <QVector>

#include "AutoDetectionReader.h"

class AutoDetectionWorker : public QObject
{
	Q_OBJECT
	struct Record
	{
		QString	windowName;
		int type;
		int onConflictBehaviour;
	};
	QVector<Record> records;
	AutoDetectionReader autoDetectionReader = AutoDetectionReader();
	bool doWork = true;
	QMainWindow* parent;
public:
	AutoDetectionWorker(QMainWindow* parent = nullptr);
	void loadAutoDetectedWindows();
	void work();
};

