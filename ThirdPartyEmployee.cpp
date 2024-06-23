#include "ThirdPartyEmployee.h"
#include "SerializeFunctions.h"

ThirdPartyEmployee::ThirdPartyEmployee() : User() {}

ThirdPartyEmployee::ThirdPartyEmployee(const MyString& name, const MyString& surname, unsigned EGN, unsigned age, unsigned password) :
	User(name, surname, EGN, age, password) {}

const typeUser& ThirdPartyEmployee::getTypeOfUser()const
{
	return typeUser::thirdParty;
}

void ThirdPartyEmployee::help()const
{
	std::cout << "List of commands:" << std::endl;
	std::cout << "- whoami()" << std::endl << "- sendCheck(sum, bankName, EGN)" << std::endl;
}

void ThirdPartyEmployee::whoami()const
{
	std::cout << "You are " + getName() + getSurname() << std::endl;
	std::cout << "Age: " + getAge() << std::endl << "EGN:" + getEGN() << std::endl;
}

void ThirdPartyEmployee::writeToFile(std::ofstream& ofs) const
{
	Person::writeToFile(ofs);

	unsigned pass = getPassword();
	ofs.write((const char*)&pass, sizeof(unsigned));

}

void ThirdPartyEmployee::readFromFiLe(std::ifstream& ifs)
{
	Person::readFromFiLe(ifs);

	unsigned pass = 0;
	ifs.read((char*)&pass, sizeof(unsigned));
	setPassword(pass);
}
