#pragma once

#include <QSettings>

class Settings
{
public:
	static Settings* settings;
	QSettings qSettings = QSettings("Luminatione", "DownloadGuard");
};

