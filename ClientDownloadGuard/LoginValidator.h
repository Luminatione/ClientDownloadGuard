#pragma once
#include "Validator.h"

class LoginValidator : IValidator
{
public:
	bool isValid(QString text) override;
};
