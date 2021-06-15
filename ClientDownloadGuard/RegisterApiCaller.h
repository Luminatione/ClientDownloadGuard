#pragma once
#include "RESTApiCaller.h"

struct RegisterApiCallerArguments
{
	QString username;
	QString password;
};
class RegisterApiCaller :
    public RESTApiCaller<RegisterApiCallerArguments>
{
	
};

