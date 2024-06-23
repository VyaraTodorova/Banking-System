#include "Person.h"
#include "SerializeFunctions.h"

Person::Person() : name(""), surname(""), EGN(0), age(0) {}
Person::Person(const MyString& name, const MyString& surname, unsigned EGN, unsigned age) :
	name(name), surname(surname), EGN(EGN), age(age) {}

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

void Person::setName(const MyString& name)
{
	this->name = name;
}

void Person::setSurname(const MyString& surname)
{
	this->surname = surname;
}

void Person::setEGN(unsigned EGN)
{
	this->EGN = EGN;
}

void Person::setAge(unsigned age)
{
	this->age = age;
}

void Person::writeToFile(std::ofstream& ofs) const
{
	size_t sizeName = getName().getSize();
	ofs.write((const char*)&sizeName, sizeof(size_t));
	writeStringToFile(ofs, getName());

	size_t sizeSurname = getSurname().getSize();
	ofs.write((const char*)&sizeSurname, sizeof(size_t));
	writeStringToFile(ofs, getSurname());

	unsigned egn = getEGN();
	ofs.write((const char*)&egn, sizeof(unsigned));

	unsigned age = getAge();
	ofs.write((const char*)&age, sizeof(unsigned));

}

void Person::readFromFiLe(std::ifstream& ifs)
{
	MyString name = readStringFromFile(ifs);
	setName(name);

	MyString surname = readStringFromFile(ifs);
	setName(surname);

	unsigned EGN = 0;
	ifs.read((char*)&EGN, sizeof(unsigned));
	setEGN(EGN);

	unsigned age = 0;
	ifs.read((char*)&age, sizeof(unsigned));
	setAge(age);

}