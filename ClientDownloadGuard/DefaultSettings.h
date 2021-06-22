#pragma once
#include <QString>

class DefaultSettings
{
public:
	static DefaultSettings* settings;

	QString defaultHostname = "192.168.1.110";
	QString defaultPort = "5000";
	QString defaultProtocol = "http://";
	bool defaultRunOnStartup = false;
	int defaultProtocolComboboxIndex = 0;
};
DefaultSettings* DefaultSettings::settings = new DefaultSettings();