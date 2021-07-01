#pragma once
#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QMutex>

#include "AutoDetectionIO.h"

class AutoDetectionService : public QObject
{

	Q_OBJECT
	QVector<AutoDetectionRecord> records;
	AutoDetectionIO autoDetectionIO = AutoDetectionIO();
	QVector<HWND> checkedWindows;

	mutable  QMutex mutex;

	bool doWork = true;
	int networkState = -1;
signals:
	void onNotify(int, QString&);
	void onUpdate();
	void onSetState(int, QString&);
public:
	AutoDetectionService();
	void setState(int state);
	void work();
public slots:
	void loadAutoDetectedWindows();
	bool hasConnection();
	HWND getWindowWithName(QString& windowName);
	bool isNetworkFree();
	bool networkStateShouldBeIgnored(int conflictBehaviour);
	bool shouldNotifyUserOnConflict(int conflictBehaviour);
	bool wantsToChangeState(int type);
};

