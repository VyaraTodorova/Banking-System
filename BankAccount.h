#pragma once
#include "MyString.h"
class BankAccount
{
public:
	BankAccount();
	BankAccount(unsigned accountNumber, unsigned amount, MyString bankName);

	void setAmount(unsigned newAmount);
	void setBankName(const MyString& newName);
	void setAccountNumber(unsigned newNumber);

	const MyString& getBankName()const;
	unsigned getAmount()const;
	unsigned getAccountNumber()const;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFiLe(std::ifstream& ifs);
private:
	MyString bankName = "";
	unsigned accountNumber = 0;
	unsigned amount = 0;
};
