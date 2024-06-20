#include "Check.h"
#include "Utils.h"
constexpr unsigned CHECK_LEN = 3;

Check::Check() : check("", 0) {}

Check::Check(const MyString& code, unsigned int price)
{
	if (isGood(code.c_str()))
	{
		check.setLhs(code);
		check.setRhs(price);
	}
	else
	{
		check.setLhs("0");
		check.setRhs(0);
	}
}

bool Check::isGood(const char* str)const
{
	if (strLen(str) != CHECK_LEN)
	{
		return false;
	}

	while (*str)
	{
		if (!(isDigit(*str) || isUpper(*str) || isLower(*str)))
		{
			return false;
		}
		str++;
	}

	return true;
}

