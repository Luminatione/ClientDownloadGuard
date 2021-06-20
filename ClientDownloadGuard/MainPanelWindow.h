#pragma once

#include <qmainwindow.h>
#include <QSharedPointer>
#include <QNetworkReply>
#include <qpointer.h>



#include "LabelTextSetter.h"
#include "ui_MainPanelWindow.h"

class MainPanelWindow : public QMainWindow
{
	Q_OBJECT

	Ui::MainPanelWindow ui;
	QPixmap networkIsBusyIcon;
	QPixmap askNotToDownloadIcon;
	QPixmap networkIsFreeIcon;
	QPixmap noConnection;

	QString authKey;

	QSharedPointer<QNetworkReply> replyGet;
	QSharedPointer<QNetworkReply> replySet;

	LabelTextSetter authorLabelTextSetter;
	LabelTextSetter descriptionLabelTextSetter;
	
public:
	void initializeLabelTextSetters();
	MainPanelWindow(QString authKey, QWidget* parent = Q_NULLPTR);
	
	void setAuthKey(QString& authKey);
	
private:
	void initializeIcons();
	void setupConnections();
	void populateStateSelection();
	void getState();
	void setIcon(int type);
private slots:
	void setState();
	void onAboutTriggered();
	void onGetStateResponse();
	void onGetStateError(QNetworkReply::NetworkError errorCode);
	void onSetStateResponse();
	void onSetStateError(QNetworkReply::NetworkError errorCode);
};

