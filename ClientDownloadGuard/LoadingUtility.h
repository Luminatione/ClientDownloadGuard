#pragma once

#include <QMovie>

class QMainWindow;

class LoadingUtility
{
	QSharedPointer<QMainWindow> mainWindow;
	QSharedPointer<QLabel> label;
	QSharedPointer<QMovie> movie;

	bool _isLoading = false;
	void setAllWidgetsEnabledState(bool state);
	QLabel* getCenteredLabelWithLoadingAnimation();
public:
	explicit LoadingUtility(QMainWindow* mainWindow);
	
	void startLoading();
	void stopLoading();
	bool isLoading();

};

