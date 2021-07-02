#include "Service.h"

void Service::setState(int state)
{
	QMutexLocker<QMutex>locker(&mutex);
	networkState = state;
}

bool Service::isNetworkFree()
{
	return networkState == 0;
}

bool Service::networkStateShouldBeIgnored(int conflictBehaviour)
{
	return conflictBehaviour == 0;
}

bool Service::shouldNotifyUserOnConflict(int conflictBehaviour)
{
	return conflictBehaviour == 1;
}

bool Service::wantsToChangeState(int type)
{
	return type != 3;
}
