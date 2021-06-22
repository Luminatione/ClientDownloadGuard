#include "SettingsWindow.h"


SettingsWindow::SettingsWindow()
{
	ui.setupUi(this);
	initializeProtocolSelection();

	setSavedOrDefaultSettings();
}

void SettingsWindow::initializeProtocolSelection()
{
	ui.connectionProtocoloComboBox->addItems({ "http://", "https://" });
	ui.connectionProtocoloComboBox->setItemData(1, false, Qt::UserRole - 1);
}

void SettingsWindow::setSavedOrDefaultSettings()
{
	ui.connectionProtocoloComboBox->setCurrentIndex(settings->value("protocolIndex", defaultProtocolComboboxIndex).toInt());
	ui.hostnameLineEdit->setText(settings->value("hostname", defaultHostname).toString());
	ui.portLineEdit->setText(settings->value("port", defaultPort).toString());
	ui.runOnStartupCheckBox->setChecked(settings->value("runOnStartup", defaultProtocolComboboxIndex).toBool());
}

