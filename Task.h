#pragma once
#include "MyString.h"
#include "Person.h"
#include "BankAccount.h"

enum TypeTask {
	Open,
	Close,
	Change,
	Unknown
};

class Task
{
public:
	Task();
	Task(TypeTask type, const MyString& name, const Person& person, const MyString& bank, const BankAccount& account);

	TypeTask getType()const;
	const MyString& getName() const;
	unsigned getEGNOfUser()const;
	const MyString& getBankName()const;
	bool getApproved()const;
	unsigned getAccountAmount()const;

	void makeApprovedTrue();
	void viewTask()const;

private:
	TypeTask type;
	MyString name;
	Person user;
	MyString bank; 
	BankAccount account;
	bool approved = false;
};


