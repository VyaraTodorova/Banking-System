#pragma once
#include "MyString.h"

class Person
{
public:
	Person(const MyString name, const MyString surname, unsigned EGN, unsigned age);
	const MyString& getName()const;
	const MyString& getSurname()const;
	unsigned getEGN()const;
	unsigned getAge()const;

private:
	MyString name;
	MyString surname;
	unsigned EGN = 0;
	unsigned age = 0;
};

