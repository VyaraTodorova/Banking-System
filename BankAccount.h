#pragma once
#include "MyString.h"
class BankAccount
{
public:
	BankAccount();
	BankAccount(unsigned accountNumber, unsigned amount, MyString bankName);

	void setAmount(unsigned newAmount);

	const MyString& getBankName()const;
	unsigned getAmount()const;
	unsigned getAccountNumber()const;

private:
	MyString bankName = "";
	unsigned accountNumber = 0;
	unsigned amount = 0;
};
