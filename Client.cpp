#include "Client.h"

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
	std::cout << "You are " + getName() + getSurname() << std::endl;
	std::cout << "Age: " + getAge() << std::endl << "EGN:" + getEGN() << std::endl;
}

void Client::addCheck(const Check& check)
{
	cashedChecks.add(check);
}

void Client::addMessage(const MyString& mess)
{
	messages.add(mess);
}

void Client::addAccount(unsigned accountNumber, unsigned amount, MyString bankName)
{
	BankAccount account(accountNumber, amount, bankName); //???
	accounts.add(account);
}

void Client::showAmountInAccount(const MyString& bankName, unsigned accountNumber)const
{
	for (int i = 0; i < accounts.getCount(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber && accounts[i].getBankName() == bankName)
		{
			std::cout << accounts[i].getAmount() << "$";
			return;
		}
	}

	throw std::invalid_argument("This account does not exist.");
}

const BankAccount& Client::getAccount(unsigned accountNumber)const
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

const MyString& Client::getNameOfBankAccount(unsigned index)const
{
	return accounts[index].getBankName();
}

unsigned Client::getAccountNumberFromIndex(unsigned index)const
{
	return accounts[index].getAccountNumber();
}

void Client::showMessages()const
{
	for (int i = 0; i < messages.getCount(); i++)
	{
		std::cout << "[" << i << "] - " << messages[i] << std::endl;
	 }
}

