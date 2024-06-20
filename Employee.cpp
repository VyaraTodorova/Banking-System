#include "Employee.h"

const MyString& getStringWithTaskType(const TypeTask& type)
{
	switch (type)
	{
	case 0: return "Open";
	case 1: return "Close";
	case 2: return "Change";
	default: return "Unknown";
	}
}

Employee::Employee() : User(), bankName("") {}

Employee::Employee(const MyString& name, const MyString& surname, unsigned EGN, unsigned age,
	unsigned password, const MyString& bankName) :
	User(name, surname, EGN, age, password), bankName(bankName) {}

unsigned Employee::getTasksCount()const
{
	return tasksCollection.getCount();
}

const typeUser& Employee::getTypeOfUser() const
{
	return typeUser::employee;
}

const MyString& Employee::getBankName()const
{
	return bankName;
}

const Task& Employee::getTask(unsigned index)const
{
	return tasksCollection[index];
}

void Employee::help()const
{
	std::cout << "List of commands:" << std::endl;
	std::cout << "- whoami()" << std::endl << "- tasks()" << std::endl << "- view(taskId)" << std::endl;
	std::cout << "- approve(taskId)" << std::endl << "- disapprove(taskId)" << std::endl;
	std::cout << "- validate(taskId)" << std::endl;
}

void Employee::whoami()const
{
	std::cout << "You are " + getName() + getSurname() << std::endl;
	std::cout << "Age: " + getAge() << std::endl << "EGN:" + getEGN() << std::endl;
}

void Employee::addTask(const MyString& bankName, const Person& user, TypeTask type, const MyString& name, const BankAccount& account)
{
	Task task(type, name, user, bankName, account);
	tasksCollection.add(task);
}

void  Employee::showAllTasks()const
{
	for (int i = 0; i < tasksCollection.getCount(); i++)
	{
		std::cout << "[" << i << "] " << getStringWithTaskType(tasksCollection[i].getType());

		if (tasksCollection[i].getType())
		{
			if (tasksCollection[i].getApproved())
			{
				std::cout << " (approved) ";
			}
		}
		std::cout << "- " + tasksCollection[i].getName();
	}
}

void Employee::removeTask(unsigned index)
{
	tasksCollection.remove(index);
}
