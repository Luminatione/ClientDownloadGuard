#include "SettingsWindow.h"
#include "QtMacros.h"
#include "DefaultSettings.h"
#include "ServerConnectionManager.h"

SettingsWindow::SettingsWindow()
{
	ui.setupUi(this);
	initializeProtocolSelection();
	setSavedOrDefaultSettings();
	initializeConnections();
}

void SettingsWindow::initializeProtocolSelection()
{
	ui.connectionProtocoloComboBox->addItems({ "http://", "https://" });
	ui.connectionProtocoloComboBox->setItemData(1, false, Qt::UserRole - 1);
}

void SettingsWindow::setAndShowAuthKey(QString authKey)
{
	this->authKey = authKey;
	ui.authKeyLineEdit->setText(authKey);
}


void SettingsWindow::setSavedOrDefaultSettings()
{
	ui.connectionProtocoloComboBox->setCurrentIndex(settings.value("protocolIndex", DefaultSettings::settings->defaultProtocolComboboxIndex).toInt());
	ui.hostnameLineEdit->setText(settings.value("hostname", DefaultSettings::settings->defaultHostname).toString());
	ui.portLineEdit->setText(settings.value("port", DefaultSettings::settings->defaultPort).toString());
	ui.runOnStartupCheckBox->setChecked(settings.value("runOnStartup", DefaultSettings::settings->defaultProtocolComboboxIndex).toBool());
}

void SettingsWindow::initializeConnections()
{
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.okButton, onOkClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.cancelButton, onCancelClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.applyButton, onApplyClick());
	BUTTON_CLICK_TO_THIS_CONNECTION(ui.showAuthKeyButton, onShowHideAuthKeyClick());
}

QString SettingsWindow::getSelectedProtocol()
{
	return ui.connectionProtocoloComboBox->currentText();
}

void SettingsWindow::onOkClick()
{
	onApplyClick();
	close();
}

void SettingsWindow::onCancelClick()
{
	close();
}

void SettingsWindow::onApplyClick()
{
	settings.setValue("protocolIndex", ui.connectionProtocoloComboBox->currentIndex());
	settings.setValue("protocol", ui.connectionProtocoloComboBox->currentText());
	settings.setValue("hostname", ui.hostnameLineEdit->text());
	settings.setValue("port", ui.portLineEdit->text());
	settings.setValue("runOnStartup", ui.runOnStartupCheckBox->isChecked());
	QString a = settings.fileName();
	ServerConnectionManager::serverConnectionManager->syncWithSettings();
}

void SettingsWindow::onShowHideAuthKeyClick()
{
	if(ui.showAuthKeyButton->text()=="Show")
	{
		ui.authKeyLineEdit->setEchoMode(QLineEdit::Normal);
		ui.showAuthKeyButton->setText("Hide");
	}
	else
	{
		ui.authKeyLineEdit->setEchoMode(QLineEdit::Password);
		ui.showAuthKeyButton->setText("Show");
	}

}
