#pragma once
#include "Validator.h"
class PasswordValidator : public Validator
{
	int minLength = 8;
	int maxLength = 32;
	QString charSet =
		"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789!@#$%^&*()-_=+";
public:
	bool isValid(QString text) override;
};

