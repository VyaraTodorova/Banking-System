#include "Task.h"
const MyString& getaStringFromTaskType(const TypeTask& type)
{
	switch (type)
	{
	case 0: return "Open";
	case 1: return "Close";
	case 2: return "Change";
	default: return "Unknown";
	}
}

Task::Task() : type(TypeTask::Unknown), name(), user(), bank(), account() {}

Task::Task(TypeTask type, const MyString& name, const Person& person,const MyString& bank, const BankAccount& account) :
	type(type), name(name), user(person), bank(bank), account(account) {}

TypeTask Task::getType()const
{
	return type;
}

const MyString& Task::getName() const
{
	return name;
}

unsigned Task::getEGNOfUser()const
{
	return user.getEGN();
}

const MyString& Task::getBank()const
{
	return bank;
}

bool Task::getApproved()const
{
	return approved;
}

unsigned Task::getAccountAmount()const
{
	return account.getAmount();
}

unsigned Task::getAccountNumber()const
{
	return account.getAccountNumber();
}
void Task::setAccountBalance(unsigned newBalance)
{
	account.setAmount(newBalance);
}
void Task::makeApprovedTrue()
{
	approved = true;
}

void Task::viewTask()const
{
	std::cout << getaStringFromTaskType(type) << " request from: " << std::endl;
	std::cout << "Name: " << user.getName() << std::endl;
	std::cout << "Surname: " << user.getSurname() << std::endl;
	std::cout << "EGN: " << user.getEGN() << std::endl;
	std::cout << "Age: " << user.getAge() << std::endl;
	std::cout << "Bank: " << bank << std::endl;

	if (account.getAccountNumber() != 0)
	{
		std::cout << "Account number: " << account.getAccountNumber() << std::endl;
		std::cout << "Balance: " << account.getAmount() << std::endl;
	}
}

