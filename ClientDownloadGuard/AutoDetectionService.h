#pragma once
#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QMutex>

#include "AutoDetectionIO.h"
#include "Service.h"

class AutoDetectionService : public Service
{

	Q_OBJECT
	QVector<AutoDetectionRecord> records;
	AutoDetectionIO autoDetectionIO = AutoDetectionIO();
	QVector<HWND> checkedWindows;

	bool doWork = true;
public:
	AutoDetectionService();
	void work() override;
public slots:
	void loadAutoDetectedWindows();
	bool hasConnection();
	HWND getWindowWithName(QString& windowName);
};

