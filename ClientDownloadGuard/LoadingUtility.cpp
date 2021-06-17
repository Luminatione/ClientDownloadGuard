#include <QMainWindow>
#include <QLabel>
#include <QMovie>

#include "LoadingUtility.h"

void LoadingUtility::startLoading()
{
	label = QSharedPointer<QLabel>(getCenteredLabelWithLoadingAnimation());
	setAllWidgetsEnabledState(false);
	movie->start();
	_isLoading = true;
}

void LoadingUtility::stopLoading()
{
	label.clear();
	setAllWidgetsEnabledState(true);
	_isLoading = false;
}

bool LoadingUtility::isLoading()
{
	return _isLoading;
}

void LoadingUtility::setAllWidgetsEnabledState(bool state)
{
	auto widgets = mainWindow->findChildren<QWidget*>();
	foreach(auto widget, widgets)
	{
		widget->setEnabled(state);
	}
}

QLabel* LoadingUtility::getCenteredLabelWithLoadingAnimation()
{
	QLabel* label = new QLabel(mainWindow);
	label->setMovie(movie.get());
	label->show();
	label->setFixedWidth(30);
	label->move((mainWindow->width() - label->width()) / 2, (mainWindow->height() - label->height()) / 2); //positionig label to center of window
	return label;
}

LoadingUtility::LoadingUtility(QMainWindow* mainWindow): mainWindow(mainWindow)
{
	movie = QSharedPointer<QMovie>(new QMovie(":/Graphic/Graphic/loader.gif"));
	label = Q_NULLPTR;
}
