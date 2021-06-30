#pragma once
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

template <class T, class TValidator = decltype(std::declval<QDataStream&>() << std::declval<T&>())> class  DataRecordIO
{
protected:
	QString fileName;
	QFile file;
	QDataStream dataStream;


public:
	virtual ~DataRecordIO() = default;
	explicit DataRecordIO(const QString& fileName) : fileName(fileName)
	{
		file.setFileName(fileName);
		if (!file.open(QIODeviceBase::ReadWrite) && file.exists())
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open file");
		}
		dataStream.setDevice(&file);
	}
	DataRecordIO() {
	}
	virtual T getNextRecord()
	{
		T record;
		dataStream >> record;
		return record;
	}
	virtual void saveRecord(T record)
	{
		dataStream << record;
	}
	virtual void truncate()
	{
		closeFile();
		file.open(QIODevice::ReadWrite | QIODevice::Truncate);
	}
	virtual void closeFile()
	{
		file.flush();
		file.close();
	}
	virtual void resetFileCursor()
	{
		file.seek(0);
	}
	virtual bool atEnd()
	{
		return dataStream.atEnd();
	}
};