#pragma once
#include <QMutex>
#include <QObject>
#include <qtmetamacros.h>

class Service : public QObject
{
	Q_OBJECT;

	mutable QMutex mutex;
	int networkState = -1;
public:
	void setState(int state);
	virtual void work() = 0;
signals:
	void updateNetworkState(int, QString&);
	void notify(int, QString&, QString&);
	void refresh();
protected:
	bool isNetworkFree();
	bool networkStateShouldBeIgnored(int conflictBehaviour);
	bool shouldNotifyUserOnConflict(int conflictBehaviour);
	bool wantsToChangeState(int type);
};

