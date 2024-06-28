#pragma once
#include "MyString.h"

class Person
{
public:
	Person();
	Person(const MyString& name, const MyString& surname, unsigned EGN, unsigned age);
	const MyString& getName()const;
	const MyString& getSurname()const;
	unsigned getEGN()const;
	unsigned getAge()const;

	void setName(const MyString& name);
	void setSurname(const MyString& surname);
	void setEGN(unsigned EGN);
	void setAge(unsigned age);

	void writeToFile(std::ofstream& ofs) const;
	void readFromFiLe(std::ifstream& ifs);
private:
	MyString name = "";
	MyString surname = "";
	unsigned EGN = 0;
	unsigned age = 0;
};

