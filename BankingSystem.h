#pragma once
#include "Client.h"
#include "Employee.h"
#include "ThirdPartyEmployee.h"
#include "Collection.hpp"

constexpr unsigned MAX_TASKS = 10000;

class BankingSystem
{
public:
	void login(const MyString& name, unsigned password, const MyString& role);
	void signup(const MyString& name, const MyString& surname, unsigned EGN, unsigned age, unsigned password, const MyString& role);
	void createBank(const MyString& name);
	void help()const;
	void whoami()const;
	void exit();

	void check_avl(const MyString& bankName, unsigned accountNumber)const;
	void open(const MyString& bankName);
	void close(const MyString& bankName, unsigned account_number);
	void redeem(const MyString& bankName, unsigned account_number, const MyString& code);
	void change(const MyString& newBankName, const MyString& currentBankName, unsigned account_number);
	void list(const MyString& bankName)const;
	void messages()const;

	void tasks()const;
	void view(unsigned taskId)const;
	void approve(unsigned taskId);
	void disapprove(unsigned taskId, const MyString& message);
	void validate(unsigned taskId);

	void sendCheck(unsigned sum, const MyString& bankName, unsigned EGN);

	void writeToFile() const;
	void readFromFiLe();

private:
	Collection<Client> clients;
	Collection<Employee> employees;
	Collection<ThirdPartyEmployee> thirdPartyEmployees;
	Collection<MyString> banks;

	typeUser currentUserType = typeUser::invalid;
	int currentIndex = 0;
	bool isUsed = false;

	bool checkIfBankExist(const MyString& bankName)const;
	unsigned getIndexOfTheLeastBusyEmployee(const MyString& bankName)const;
	int getIndexOfEmployee(const MyString& name, unsigned password)const;
	int getIndexOfClient(const MyString& name, unsigned password)const;
	int getIndexOfThirdPartyEmployees(const MyString& name, unsigned password)const;
	int getIndexOfClientWithEGN(unsigned EGN)const;
	unsigned getUniqueNumber()const;
	bool checkIfAccountNumberIsUnique(unsigned number)const;
	MyString getUniqueCode()const;
	bool checkIfCodeIsUnique(const MyString& code)const;
};


