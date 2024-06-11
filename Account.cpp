#include "Account.h"
Account::Account(const MyString name, const MyString surname, unsigned EGN, unsigned age, unsigned password):
	Person(name,surname,EGN,age), password(password){}

unsigned Account::getPassword()const
{
	return password;
}

void Account::exit()
{

}