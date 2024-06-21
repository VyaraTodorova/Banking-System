#pragma once

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

