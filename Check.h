#pragma once
#include "Pair.hpp"
#include "MyString.h"


class Check
{
public:
	Check();
	Check(const MyString& code, unsigned int price);
private:
	Pair<MyString, unsigned int > check;
	bool isGood(const char* str)const;
};

