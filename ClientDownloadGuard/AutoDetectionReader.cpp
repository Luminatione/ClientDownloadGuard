#include "AutoDetectionReader.h"

#include <QMessageBox>

AutoDetectionReader* AutoDetectionReader::autoDetectionReader = new AutoDetectionReader();


AutoDetectionReader::AutoDetectionReader()
{
	QMutexLocker<QMutex> locker(&mutex);
	if (!file.open(QIODeviceBase::ReadWrite) && file.exists())
	{
		QMessageBox::critical(nullptr, "Error", "Failed to open file");
	}
	QString a = file.fileName();
}

std::tuple<QString, int, int> AutoDetectionReader::getNextRecord()
{
	QMutexLocker<QMutex> locker(&mutex);
	QString windowName;
	int type;
	int conflictBehaviour;
	dataStream >> windowName >> type >> conflictBehaviour;
	return { windowName, type, conflictBehaviour };
}

void AutoDetectionReader::saveRecord(QString& windowName, int type, int conflictBehaviour)
{
	QMutexLocker<QMutex> locker(&mutex);
	dataStream << windowName << type << conflictBehaviour;
}

void AutoDetectionReader::truncate()
{
	QMutexLocker<QMutex> locker(&mutex);
	closeFile();
	file.open(QIODevice::ReadWrite | QIODevice::Truncate);
}

void AutoDetectionReader::closeFile()
{
	QMutexLocker<QMutex> locker(&mutex);
	file.flush();
	file.close();
}

void AutoDetectionReader::resetFileCursor()
{
	QMutexLocker<QMutex> locker(&mutex);
	file.seek(0);
}

bool AutoDetectionReader::atEnd()
{
	return dataStream.atEnd();
}

AutoDetectionReader::~AutoDetectionReader()
{
	QMutexLocker<QMutex> locker(&mutex);
	closeFile();
}
