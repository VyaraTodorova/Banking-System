#pragma once
#include "Pair.hpp"
#include "MyString.h"

class Check
{
public:
	Check();
	Check(const MyString& code, unsigned int price);

	void setSum(unsigned sum);

	unsigned getSum()const;
	const MyString& getCode()const;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFiLe(std::ifstream& ifs);
private:
	Pair<MyString, unsigned int > check = {"",0};

	bool isGood(const char* str)const;
};

