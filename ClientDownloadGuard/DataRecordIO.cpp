//#include "DataRecordIO.h"
//
//#include <QMessageBox>
//
//template <class T, class T0>
//DataRecordIO<T, T0>::DataRecordIO(const QString& fileName) : fileName(fileName)
//{
//	file.setFileName(fileName);
//	if (!file.open(QIODeviceBase::ReadWrite) && file.exists())
//	{
//		QMessageBox::critical(nullptr, "Error", "Failed to open file");
//	}
//	dataStream.setDevice(&file);
//}
//
//template <class T, class T0>
//DataRecordIO<T, T0>::DataRecordIO()
//{
//}
//
//template <class T, class T0>
//T DataRecordIO<T, T0>::getNextRecord()
//{
//	T record;
//	dataStream >> record;
//	return record;
//}
//
//template <class T, class T0>
//void DataRecordIO<T, T0>::saveRecord(T record)
//{
//	dataStream << record;
//}
//
//template <class T, class T0>
//void DataRecordIO<T, T0>::truncate()
//{
//	closeFile();
//	file.open(QIODevice::ReadWrite | QIODevice::Truncate);
//}
//
//template <class T, class T0>
//void DataRecordIO<T, T0>::closeFile()
//{
//	file.flush();
//	file.close();
//}
//
//template <class T, class T0>
//void DataRecordIO<T, T0>::resetFileCursor()
//{
//	file.seek(0);
//}
//
//template <class T, class T0>
//bool DataRecordIO<T, T0>::atEnd()
//{
//	return dataStream.atEnd();
//}
