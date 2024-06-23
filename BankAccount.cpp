#include "BankAccount.h"
#include "SerializeFunctions.h"

BankAccount::BankAccount() : accountNumber(0), amount(0) {}

BankAccount::BankAccount(unsigned accountNumber, unsigned amount, MyString bankName) :
	accountNumber(accountNumber), amount(amount), bankName(bankName) {}

void BankAccount::setAmount(unsigned newAmount)
{
	amount = newAmount;
}

void BankAccount::setBankName(const MyString& newName)
{
	bankName = newName;
}

void BankAccount::setAccountNumber(unsigned newNumber)
{
	accountNumber = newNumber;
}

unsigned BankAccount::getAmount()const
{
	return amount;
}

unsigned BankAccount::getAccountNumber()const
{
	return accountNumber;
}

const MyString& BankAccount::getBankName()const
{
	return bankName;
}

void BankAccount::writeToFile(std::ofstream& ofs) const
{
	writeStringToFile(ofs, bankName);
	ofs.write((const char*)&accountNumber, sizeof(unsigned));
	ofs.write((const char*)&amount, sizeof(unsigned));
}

void BankAccount::readFromFiLe(std::ifstream& ifs)
{
	bankName = readStringFromFile(ifs);
	ifs.read((char*)&accountNumber, sizeof(unsigned));
	ifs.read((char*)&amount, sizeof(unsigned));
}