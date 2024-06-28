#include "Client.h"
#include "SerializeFunctions.h"

Client::Client() : User(), address("") {}

Client::Client(const MyString& name, const MyString& surname, unsigned EGN, unsigned age, unsigned password, const MyString& address) :
	User(name, surname, EGN, age, password), address(address) {}

const typeUser& Client::getTypeOfUser()const
{
	return typeUser::client;
}

void Client::help()const
{
	std::cout << "List of commands:" << std::endl;
	std::cout << "- whoami()" << std::endl << "- check_avl(bankName, accountNumber)" << std::endl << "- open(bankName)" << std::endl;
	std::cout << "- close(bankName, accountNumber)" << std::endl << "- redeem(bankName, accountNumber, code)" << std::endl;
	std::cout << "- change(newBankName, currentBankName, accountNumber)" << std::endl << "- list(bankName)" 
		<< std::endl << "- messages()" << std::endl;
}

void Client::whoami()const
{
	std::cout << "You are " << getName() << " " << getSurname() << std::endl
	<< "Age: " << getAge() << std::endl << "EGN:" << getEGN() << std::endl;
}

void Client::addCheck(const Check& check)
{
	checks.add(check);
}

int Client::getIndexOfCheck(const MyString& code)const
{
	for (int i = 0; i < checks.getCount(); i++)
	{
		if (code == checks[i].getCode())
		{
			return i;
		}
	}

	return -1;
}

void Client::cashCheck(unsigned checkIndex, unsigned accountIndex)
{
	unsigned oldAmount = accounts[accountIndex].getAmount();
	accounts[accountIndex].setAmount(oldAmount + checks[checkIndex].getSum());

	cashedChecks.add(checks[checkIndex]);
	checks.remove(checkIndex);
}

bool Client::checkIfCodeIsUniqueForPerson(const MyString& code)const
{
	for (int i = 0; i < checks.getCount(); i++)
	{
		if (checks[i].getCode() == code)
		{
			return false;
		}
	}

	for (int i = 0; i < cashedChecks.getCount(); i++)
	{
		if (cashedChecks[i].getCode() == code)
		{
			return false;
		}
	}

	return true;
}

void Client::addMessage(const MyString& mess)
{
	messages.add(mess);
}

void Client::addAccount(const BankAccount& account)
{
	accounts.add(account);
}

void Client::closeAccount(unsigned accountNumber)
{
	for (int i = 0; i < accounts.getCount(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber)
		{
			accounts.remove(i);
		}
	}
}

void Client::changeAccountBank(unsigned accountNumber, const MyString& newBankName, unsigned newAccountNumber)
{
	for (int i = 0; i < accounts.getCount(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber)
		{
			accounts[i].setBankName(newBankName);
			accounts[i].setAccountNumber(newAccountNumber);
		}
	}
}

void Client::showAmountInAccount(const MyString& bankName, unsigned accountNumber)const
{
	for (int i = 0; i < accounts.getCount(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber && accounts[i].getBankName() == bankName)
		{
			std::cout << accounts[i].getAmount() << "$" << std::endl;
			return;
		}
	}

	throw std::invalid_argument("This account does not exist.");
}

 BankAccount Client::getAccount(unsigned accountNumber)const
{
	for (int i = 0; i < accounts.getCount(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber)
		{
			return accounts[i];
		}
	}

	throw std::invalid_argument("Account with this number does not exist.");
}

unsigned Client::getCountOfAccounts()const
{
	return accounts.getCount();
}

MyString Client::getNameOfBankAccount(unsigned index)const
{
	return accounts[index].getBankName();
}

unsigned Client::getAccountNumberFromIndex(unsigned index)const
{
	return accounts[index].getAccountNumber();
}

int Client::getIndexOfAccountFromNumber(unsigned number)const
{
	for (int i = 0; i < accounts.getCount(); i++)
	{
		if (accounts[i].getAccountNumber() == number)
		{
			return i;
		}
	}

	return -1;
}

bool Client::checkIfAccountNumberIsUniqueForPerson(unsigned number)const
{
	for (int i = 0; i < accounts.getCount(); i++)
	{
		if (accounts[i].getAccountNumber() == number)
		{
			return false;
		}
	}

	return true;
}
void Client::showMessages()const
{
	for (int i = 0; i < messages.getCount(); i++)
	{
		std::cout << "[" << i << "] - " << messages[i] << std::endl;
	 }
}

void Client::clearAllMessages()
{
	messages.clear();
}

void Client::writeToFile(std::ofstream& ofs) const
{
	Person::writeToFile(ofs);

	unsigned pass = getPassword();
	ofs.write((const char*)&pass, sizeof(unsigned));

	writeStringToFile(ofs, address);

	size_t countChecks = checks.getCount();
	ofs.write((const char*)&countChecks, sizeof(size_t));

	for (int i = 0; i < countChecks; i++)
	{
		checks[i].writeToFile(ofs);
	}

	size_t countCashedChecks = cashedChecks.getCount();
	ofs.write((const char*)&countCashedChecks, sizeof(size_t));

	for (int i = 0; i < countCashedChecks; i++)
	{
		cashedChecks[i].writeToFile(ofs);
	}

	size_t countMess = messages.getCount();
	ofs.write((const char*)&countMess, sizeof(size_t));

	for (int i = 0; i < countMess; i++)
	{
		writeStringToFile(ofs, messages[i].c_str());
	}

	size_t countAccounts = accounts.getCount();
	ofs.write((const char*)&countAccounts, sizeof(size_t));

	for (int i = 0; i < countAccounts; i++)
	{
		accounts[i].writeToFile(ofs);
	}
}

void Client::readFromFiLe(std::ifstream& ifs)
{
	Person::readFromFiLe(ifs);

	unsigned pass = 0;
	ifs.read((char*)&pass, sizeof(unsigned));
	setPassword(pass);

	address = readStringFromFile(ifs);

	size_t countChecks = 0;
	ifs.read((char*)&countChecks, sizeof(size_t));

	for (int i = 0; i < countChecks; i++)
	{
		Check check;
		check.readFromFiLe(ifs);
		cashedChecks.add(check);
	}

	size_t countMess = 0;
	ifs.read((char*)&countMess, sizeof(size_t));

	for (int i = 0; i < countMess; i++)
	{
		MyString mess = readStringFromFile(ifs);
		messages.add(mess);
	}

	size_t countAccounts = 0;
	ifs.read((char*)&countAccounts, sizeof(size_t));

	for (int i = 0; i < countAccounts; i++)
	{
		BankAccount ba;
		ba.readFromFiLe(ifs);
		accounts.add(ba);
	}
}
