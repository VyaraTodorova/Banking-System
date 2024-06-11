#pragma once
#include "Person.h"

class Account: public Person
{
	Account(const MyString name, const MyString surname, unsigned EGN, unsigned age, unsigned password);
	unsigned getPassword()const;
	void exit();
	virtual void whoami() const = 0;
	virtual void help() const = 0;
private:
	unsigned password = 0;
};

