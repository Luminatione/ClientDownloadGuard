#pragma once
#include <QFile>
#include <QString>
#include <QCoreApplication>
#include <QMutex>

class AutoDetectionReader
{
	QString fileName = "auto detection.dat";
	QFile file = QFile(fileName);
	QDataStream dataStream = QDataStream(&file);

public:

	AutoDetectionReader();

	std::tuple<QString, int, int> getNextRecord();
	void saveRecord(QString& windowName, int type, int conflictBehaviour);
	void truncate();
	void closeFile();
	void resetFileCursor();
	bool atEnd();
	~AutoDetectionReader();
};

