#pragma once
#include <QSettings>

#include "ui_SettingsWindow.h"

class SettingsWindow : public QMainWindow
{
	Q_OBJECT

public:
	void setSavedOrDefaultSettings();
	void initializeProtocolSelection();
	SettingsWindow();
private:
	Ui::SettingsWindow ui;
	QSharedPointer<QSettings> settings = QSharedPointer<QSettings>(new QSettings());

	QString defaultHostname = "192.168.1.110";
	QString defaultPort = "5000";
	QString defaultProtocol = "http://";
	bool defaultRunOnStartup = false;
	int defaultProtocolComboboxIndex = 0;

};

