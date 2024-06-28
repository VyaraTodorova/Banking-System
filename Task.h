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
	const MyString& getBank()const;
	bool getApproved()const;
	unsigned getAccountAmount()const;
	unsigned getAccountNumber()const;
	void setAccountBalance(unsigned newBalance);

	void makeApprovedTrue();
	void viewTask()const;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFiLe(std::ifstream& ifs);
private:
	TypeTask type = TypeTask::Unknown;
	MyString name = "";
	Person user;
	MyString bank = "";
	BankAccount account;
	bool approved = false;
};


