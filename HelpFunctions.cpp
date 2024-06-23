#include "HelpFunctions.h"
constexpr int MAX_NUM = 40000;
constexpr int MAX_LEN_CODE = 3;

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

const char* generateCode()
{
	char code[MAX_LEN_CODE + 1];
	const char characters[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int charactersCount = sizeof(characters) - 1;

	std::srand(std::time(nullptr));

	for (int i = 0; i < MAX_LEN_CODE; ++i)
	{
		int index = std::rand() % charactersCount;
		code[i] = characters[index];
	}

	code[MAX_LEN_CODE] = '\0';
}

