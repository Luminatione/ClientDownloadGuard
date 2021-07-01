#pragma once

#include <qmainwindow.h>
#include <QSharedPointer>
#include <QNetworkReply>
#include <qpointer.h>
#include <QThread>


#include "AutoDetectionService.h"
#include "LabelTextSetter.h"
#include "ui_MainPanelWindow.h"

enum state { no_connection = -1, free_network = 0, busy_network = 1, asking_not_to_download = 2 };

class MainPanelWindow : public QMainWindow
{
	Q_OBJECT

	Ui::MainPanelWindow ui;
	QPixmap networkIsBusyIcon;
	QPixmap askNotToDownloadIcon;
	QPixmap networkIsFreeIcon;
	QPixmap noConnectionIcon;

	QString authKey;

	QSharedPointer<QNetworkReply> replyGet;
	QSharedPointer<QNetworkReply> replySet;

	LabelTextSetter authorLabelTextSetter;
	LabelTextSetter descriptionLabelTextSetter;
	
	bool offlineMode = false;
	bool awaitsSetState = false;
	AutoDetectionService* autoDetectionWorker;
	state networkState = no_connection;
	
	QThread thr = QThread();
	
public:
	void initializeLabelTextSetters();
	void startAutoDetection();
	MainPanelWindow(QString authKey, QWidget* parent = nullptr);
	~MainPanelWindow();
	void setAuthKey(QString& authKey);
	void getState();
	void onNotify(int type, QString& windowName);
	
private:
	void initializeIcons();
	void setupConnections();
	void populateStateSelection();
	void setIcon(int type);
signals:
	void becomeOnline();
public slots:
	void onSetState(int type, QString& description);
	void onRefreshClick();
	
private slots:
	void setState();
	void onAboutTriggered();
	void onSettingsTriggered();
	void onAutoDetectionTriggered();
	void onScheduleTriggered();
	void onGetStateResponse();
	void onGetStateError(QNetworkReply::NetworkError errorCode);
	void onSetStateResponse();
	void onSetStateError(QNetworkReply::NetworkError errorCode);
};

