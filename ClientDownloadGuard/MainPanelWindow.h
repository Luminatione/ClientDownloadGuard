#pragma once

#include <qmainwindow.h>
#include <QSharedPointer>
#include <QNetworkReply>


#include "LabelTextSetter.h"
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

	LabelTextSetter authorLabelTextSetter = LabelTextSetter("", "Author: ", "", ui.authorLabel);
	LabelTextSetter descriptionLabelTextSetter = LabelTextSetter("", "Description: \n", "", ui.currentDescriptionLabel);
	
public:
	MainPanelWindow(QString authKey, QWidget* parent = Q_NULLPTR);
	
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

