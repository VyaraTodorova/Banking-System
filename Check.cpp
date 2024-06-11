#include "Check.h"
constexpr int CHECK_LEN = 3;

bool isUpper(char symbol)
{
	return symbol >= 'A' && symbol <= 'Z';
}

bool isLower(char symbol)
{
	return symbol >= 'a' && symbol <= 'z';
}

bool isDigit(char symbol)
{
	return symbol >= '0' && symbol <= '9';
}

int strLen(const char* str)
{
	if (!str)
	{
		return -1;
	}

	int count = 0;

	while (*str)
	{
		count++;
		str++;
	}

	return count;
}
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
		return false;
	}

	return true;
}