#pragma once
#include "User.h"
#include "Check.h"
#include "Collection.hpp"
#include "BankAccount.h"

class Client : public User
{
public:
	Client();
	Client(const MyString& name, const MyString& surname, unsigned EGN, unsigned age, unsigned password, const MyString& address);

	const typeUser& getTypeOfUser()const override;
	void help()const override;
	void whoami()const override;

	void addCheck(const Check& check);
	void addMessage(const MyString& mess);
	void addAccount(unsigned accountNumber, unsigned amount, MyString bankName);
	void closeAccount(unsigned accountNumber);
	void changeAccountBank(unsigned accountNumber, const MyString& newBankName, unsigned newAccountNumber);

	void showAmountInAccount(const MyString& bankName, unsigned accountNumber)const;
	const BankAccount& getAccount(unsigned accountNumber)const;
	unsigned getCountOfAccounts()const;
	const MyString& getNameOfBankAccount(unsigned index)const;
	unsigned getAccountNumberFromIndex(unsigned index)const;
	bool checkIfAccountNumberIsUniqueForPerson(unsigned number)const;

	void showMessages()const;
private:
	Collection<Check> cashedChecks;
	MyString address;
	Collection<MyString> messages;
	Collection<BankAccount> accounts;

};
