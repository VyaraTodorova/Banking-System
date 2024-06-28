#include "Employee.h"
#include "SerializeFunctions.h"

const char* getStringWithTaskType(const TypeTask& type)
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
	std::cout << "You are " << getName() << " " << getSurname() << std::endl;
	std::cout << "Age: " << getAge() << std::endl << "EGN:" << getEGN() << std::endl;
}

void Employee::addTask(const Task& task)
{
	tasksCollection.add(task);
}
void  Employee::showAllTasks()const
{
	for (int i = 0; i < tasksCollection.getCount(); i++)
	{
		std::cout << "[" << i << "] " << getStringWithTaskType(tasksCollection[i].getType());

		if (tasksCollection[i].getType() == TypeTask::Change)
		{
			if (tasksCollection[i].getApproved())
			{
				std::cout << " (approved) ";
			}
		}
		std::cout << " - " + tasksCollection[i].getName() << std::endl;
	}
}

void Employee::removeTask(unsigned index)
{
	tasksCollection.remove(index);
}

void Employee::changeApproveWithIndex(unsigned index)
{
	tasksCollection[index].makeApprovedTrue();
}

void Employee::setAccountBalanceWithIndex(unsigned index, unsigned newBalance)
{
	tasksCollection[index].setAccountBalance(newBalance);
}

void Employee::writeToFile(std::ofstream& ofs) const
{
	Person::writeToFile(ofs);

	unsigned pass = getPassword();
	ofs.write((const char*)&pass, sizeof(unsigned));

	writeStringToFile(ofs, bankName);

	size_t countTasks = tasksCollection.getCount();
	ofs.write((const char*)&countTasks, sizeof(size_t));

	for (int i = 0; i < countTasks; i++)
	{
		tasksCollection[i].writeToFile(ofs);
	}
}

void Employee::readFromFiLe(std::ifstream& ifs)
{
	Person::readFromFiLe(ifs);

	unsigned pass = 0;
	ifs.read((char*)&pass, sizeof(unsigned));
	setPassword(pass);

	bankName = readStringFromFile(ifs);

	size_t countTasks = 0;
	ifs.read((char*)&countTasks, sizeof(size_t));

	for (int i = 0; i < countTasks; i++)
	{
		Task ts;
		ts.readFromFiLe(ifs);
		tasksCollection.add(ts);
	}

}
