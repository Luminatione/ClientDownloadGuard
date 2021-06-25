#pragma once
#include <QFile>
#include <QString>
#include <QCoreApplication>
#include <QMutex>

class AutoDetectionIO
{
	QString fileName = "auto detection.dat";
	QFile file = QFile(fileName);
	QDataStream dataStream = QDataStream(&file);

public:

	AutoDetectionIO();

	std::tuple<QString, int, int> getNextRecord();
	void saveRecord(QString& windowName, int type, int conflictBehaviour);
	void truncate();
	void closeFile();
	void resetFileCursor();
	bool atEnd();
	~AutoDetectionIO();
};

