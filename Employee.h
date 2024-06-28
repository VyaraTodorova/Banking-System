#pragma once
#include "User.h"
#include "MyString.h"
#include "Collection.hpp"
#include "Task.h"

class Employee : public User
{
public:
	Employee();
	Employee(const MyString& name, const MyString& surname, unsigned EGN, unsigned age,
		unsigned password, const MyString& bankName);

	const typeUser& getTypeOfUser()const override;
	void help()const override;
	void whoami()const override;

	const MyString& getBankName()const;
	unsigned getTasksCount()const;
	const Task& getTask(unsigned index)const;
	void addTask(const Task& task);
	void showAllTasks()const;
	void removeTask(unsigned index);
	void changeApproveWithIndex(unsigned index);
	void setAccountBalanceWithIndex(unsigned index, unsigned newBalance);

	void writeToFile(std::ofstream& ofs) const;
	void readFromFiLe(std::ifstream& ifs);
protected:
	MyString bankName = "";
	Collection<Task> tasksCollection;
};
