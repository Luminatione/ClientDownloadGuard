#pragma once
#include <QString>

class IValidator
{
public:
	virtual ~IValidator() = default;
	virtual bool isValid(QString text) = 0;
};