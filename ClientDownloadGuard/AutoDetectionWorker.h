#pragma once
#include <QMainWindow>
#include <QString>
#include <QVector>

#include "AutoDetectionReader.h"
#include "MainPanelWindow.h"

class AutoDetectionWorker : public QObject
{
	enum state {no_connection = -1, free = 0, busy = 1, asking_not_to_download = 2};
	Q_OBJECT
	struct Record
	{
		QString	windowName;
		int type;
		int onConflictBehaviour;
	};
	QVector<Record> records;
	AutoDetectionReader autoDetectionReader = AutoDetectionReader();
	QMainWindow* parent;

	QMutex mutex;

	bool doWork = true;
	state networkState = no_connection;
public:
	AutoDetectionWorker(QMainWindow* parent = nullptr);
	void loadAutoDetectedWindows();
	void work();
	void setState(int state);
};

