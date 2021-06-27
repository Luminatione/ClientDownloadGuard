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
	QVector<HWND> checkedWindows;

	mutable  QMutex mutex;

	bool doWork = true;
	int networkState = -1;
signals:
	void onNotify(int, QString&);
	void onUpdate();
	void onSetState(int, QString&);
public:
	AutoDetectionWorker(QMainWindow* parent = nullptr);
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

