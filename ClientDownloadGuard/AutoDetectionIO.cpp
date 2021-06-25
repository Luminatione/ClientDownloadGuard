#include "AutoDetectionIO.h"

#include <QMessageBox>

AutoDetectionIO::AutoDetectionIO()
{
	if (!file.open(QIODeviceBase::ReadWrite) && file.exists())
	{
		QMessageBox::critical(nullptr, "Error", "Failed to open file");
	}
	QString a = file.fileName();
}

std::tuple<QString, int, int> AutoDetectionIO::getNextRecord()
{
	QString windowName;
	int type;
	int conflictBehaviour;
	dataStream >> windowName >> type >> conflictBehaviour;
	return { windowName, type, conflictBehaviour };
}

void AutoDetectionIO::saveRecord(QString& windowName, int type, int conflictBehaviour)
{
	dataStream << windowName << type << conflictBehaviour;
}

void AutoDetectionIO::truncate()
{
	closeFile();
	file.open(QIODevice::ReadWrite | QIODevice::Truncate);
}

void AutoDetectionIO::closeFile()
{
	file.flush();
	file.close();
}

void AutoDetectionIO::resetFileCursor()
{
	file.seek(0);
}

bool AutoDetectionIO::atEnd()
{
	return dataStream.atEnd();
}

AutoDetectionIO::~AutoDetectionIO()
{
	closeFile();
}
