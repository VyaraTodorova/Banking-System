#pragma once
#include <ctime>
const int MAX_NUM = 40000;

char getCharFromDigit(int digit)
{
	if (digit < 0 || digit > 9)
		return '\0';
	return digit + '0';
}

unsigned getNumberLength(unsigned n)
{

	if (n == 0)
		return 1;
	unsigned res = 0;

	while (n != 0)
	{
		res++;
		n /= 10;
	}
	return res;
}


const char* toString(unsigned n)
{
	unsigned len = getNumberLength(n);
	char* str = new char[n];
	for (int i = len - 1; i >= 0; i--)
	{
		str[i] = getCharFromDigit(n % 10);
		n /= 10;
	}
	str[len] = '\0';

	return str;
}

unsigned randomNumber()
{
	std::srand(time(0));
	unsigned number = rand() % MAX_NUM + 1;

	return number;
}