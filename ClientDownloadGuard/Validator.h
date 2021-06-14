#pragma once
#include <QString>

class Validator
{
public:
	virtual ~Validator() = default;
	virtual bool isValid(QString text) = 0;
};