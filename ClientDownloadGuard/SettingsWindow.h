#pragma once
#include <QSettings>

#include "ui_SettingsWindow.h"

class SettingsWindow : public QMainWindow
{
	Q_OBJECT

public:
	SettingsWindow();
	void setSavedOrDefaultSettings();
	void initializeProtocolSelection();
	void setAndShowAuthKey(QString authKey);

private:
	Ui::SettingsWindow ui;
	
	QSettings settings = QSettings();

	QString defaultHostname = "192.168.1.110";
	QString defaultPort = "5000";
	bool defaultRunOnStartup = false;
	int defaultProtocolComboboxIndex = 0;

	QString authKey;
	
	void initializeConnections();
	QString getSelectedProtocol();
private slots:
	void onOkClick();
	void onCancelClick();
	void onApplyClick();
	void onShowHideAuthKeyClick();
};

