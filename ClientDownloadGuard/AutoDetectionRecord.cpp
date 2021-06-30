#include "AutoDetectionRecord.h"

QDataStream& operator<<(QDataStream& dataStream, AutoDetectionRecord& autoDetectionRecord)
{
	dataStream << autoDetectionRecord.windowName << autoDetectionRecord.type << autoDetectionRecord.conflictBehaviour;
	return dataStream;
}

QDataStream& operator>>(QDataStream& dataStream, AutoDetectionRecord& autoDetectionRecord)
{
	dataStream >> autoDetectionRecord.windowName >> autoDetectionRecord.type >> autoDetectionRecord.conflictBehaviour;
	return dataStream;
	
}
