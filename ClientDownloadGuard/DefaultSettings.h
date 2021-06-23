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


	int autoDetectionTableColumnWidth = 168;
	int autoDetectionWindowWidth = 605;
	int autoDetectionWindowHeight = 464;
};
DefaultSettings* DefaultSettings::settings = new DefaultSettings();