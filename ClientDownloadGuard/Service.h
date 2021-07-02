#pragma once
#include <QMutex>
#include <QObject>
#include <qtmetamacros.h>

class Service : public QObject
{
	Q_OBJECT

		mutable QMutex mutex;
	int networkState = -1;
public:
	virtual void work() = 0;
signals:
	void setState(int, QString&);
};

