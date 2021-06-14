#include "UsernameValidator.h"

bool UsernameValidator::isValid(QString text)
{
	for(auto chr : text)
	{
		if(!charSet.contains(chr))
		{
			return false;
		}
	}
	return text.length() >= minLength && text.length() <= maxLength;
}
