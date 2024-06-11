#include "Person.h"
Person::Person(const MyString name, const MyString surname, unsigned EGN, unsigned age) :
	name(name), surname(surname), EGN(EGN), age(age){}

const MyString& Person::getName()const
{
	return name;
}

const MyString& Person::getSurname()const
{
	return surname;
}

unsigned Person::getEGN()const
{
	return EGN;
}

unsigned Person::getAge()const
{
	return age;
}