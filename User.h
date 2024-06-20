#pragma once
#include "Person.h"
enum typeUser {
	client,
	employee,
	thirdParty,
	invalid
};

class User : public Person
{
public:
	User();
	User(const MyString& name, const MyString& surname, unsigned EGN, unsigned age, unsigned password);
	unsigned getPassword()const;
	virtual const typeUser& getTypeOfUser()const = 0;
	virtual void help()const = 0;
	virtual void whoami()const = 0;
	virtual ~User() = default;
private:
	unsigned password = 0;
};


