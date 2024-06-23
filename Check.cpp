#include "Check.h"
#include "Utils.h"
#include "SerializeFunctions.h"
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

void Check::setSum(unsigned sum)
{
	check.setRhs(sum);
}

unsigned Check::getSum()const
{
	return check.getRhs();
}

const MyString& Check::getCode()const
{
	return check.getLhs();
}

void Check::writeToFile(std::ofstream& ofs) const
{
	writeStringToFile(ofs, check.getLhs());
	ofs.write((const char*)&check.getRhs(), sizeof(unsigned int));
}

void Check::readFromFiLe(std::ifstream& ifs)
{
	check.setLhs(readStringFromFile(ifs));
	unsigned int checkNum = 0;
	ifs.read((char*)&checkNum, sizeof(unsigned int));
	check.setRhs(checkNum);
}
