#include "AutoDetectionReader.h"

#include <QMessageBox>

AutoDetectionReader::AutoDetectionReader()
{
	if (!file.open(QIODeviceBase::ReadWrite) && file.exists())
	{
		QMessageBox::critical(nullptr, "Error", "Failed to open file");
	}
	QString a = file.fileName();
}

std::tuple<QString, int, int> AutoDetectionReader::getNextRecord()
{
	QString windowName;
	int type;
	int conflictBehaviour;
	dataStream >> windowName >> type >> conflictBehaviour;
	return { windowName, type, conflictBehaviour };
}

void AutoDetectionReader::saveRecord(QString& windowName, int type, int conflictBehaviour)
{
	dataStream << windowName << type << conflictBehaviour;
}

void AutoDetectionReader::truncate()
{
	closeFile();
	file.open(QIODevice::ReadWrite | QIODevice::Truncate);
}

void AutoDetectionReader::closeFile()
{
	file.flush();
	file.close();
}

void AutoDetectionReader::resetFileCursor()
{
	file.seek(0);
}

bool AutoDetectionReader::atEnd()
{
	return dataStream.atEnd();
}

AutoDetectionReader::~AutoDetectionReader()
{
	closeFile();
}
