#pragma once
#include <QMainWindow>
#include <QString>
#include <QVector>

#include "AutoDetectionIO.h"

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
	AutoDetectionIO autoDetectionReader = AutoDetectionIO();
	QMainWindow* parent;
	QVector<HWND> resolvedWindows;

	mutable  QMutex mutex;

	bool doWork = true;
	int networkState = -1;
signals:
	void onNotify(int, QString&);
	void onUpdate();
public:
	AutoDetectionWorker(QMainWindow* parent = nullptr);
	void setState(int state);
	void work();
public slots:
	void loadAutoDetectedWindows();
};

