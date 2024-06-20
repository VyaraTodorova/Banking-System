#include "User.h"

User::User() : Person(), password(0) {}
User::User(const MyString& name, const MyString& surname, unsigned EGN, unsigned age, unsigned password) :
	Person(name, surname, EGN, age), password(password) {}

unsigned User::getPassword()const
{
	return password;
}
