#pragma once
#include "Validator.h"

class UsernameValidator : public Validator
{
	int minLength = 6;
	int maxLength = 20;
	QString charSet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789-_";
public:
	bool isValid(QString text) override;
};
