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

	QString authKey;
	
	void initializeConnections();
	QString getSelectedProtocol();
private slots:
	void onOkClick();
	void onCancelClick();
	void applyRunOnStartupState();
	void onApplyClick();
	void onShowHideAuthKeyClick();
};

