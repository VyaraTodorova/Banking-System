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

	void addTask(const MyString& bankName, const Person& user, TypeTask type, const MyString& name, const BankAccount& account);
	void showAllTasks()const;
	void removeTask(unsigned index);

protected:
	MyString bankName;
	Collection<Task> tasksCollection;
};
