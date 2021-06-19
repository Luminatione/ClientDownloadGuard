#pragma once

#include <qmainwindow.h>
#include <QSharedPointer>
#include <QNetworkReply>

#include "ui_MainPanelWindow.h"
class MainPanelWindow : public QMainWindow
{
	Q_OBJECT

	Ui::MainPanelWindow ui;
	QPixmap networkIsBusyIcon;
	QPixmap askNotToDownload;
	QPixmap networkIsFree;
	QPixmap noConnection;

	QString authKey;

	QSharedPointer<QNetworkReply> reply;
	
public:
	MainPanelWindow(QWidget* parent = Q_NULLPTR);
	
	void setAuthKey(QString& authKey);
	
private:
	void initializeIcons();
	void setupConnections();
	void populateStateSelection();
	void getState();
	
private slots:
	void onAboutTriggered();
	void onGetStateResponse();
	void onGetStateError(QNetworkReply::NetworkError errorCode);
};

