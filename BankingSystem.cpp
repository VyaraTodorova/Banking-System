#include "BankingSystem.h"
#include "HelpFunctions.h"
#include <fstream>
#include "SerializeFunctions.h"

void BankingSystem::login(const MyString& name, unsigned password, const MyString& role)
{
	if (role == "Client")
	{
		isUsed = true;
		currentIndex = getIndexOfClient(name,password);
		if (currentIndex == -1)
		{
			throw std::invalid_argument("Wrong name, password or/and role.");
		}
		currentUserType = typeUser::client;
	}
	else if (role == "Employee")
		{
			isUsed = true;
			currentIndex = getIndexOfEmployee(name, password);
			if (currentIndex == -1)
			{
				throw std::invalid_argument("Wrong name, password or/and role.");
			}
			currentUserType = typeUser::employee;
		}
		else if (role == "ThirdPartyEmployee")
			{
				isUsed = true;
				currentIndex = getIndexOfThirdPartyEmployees(name, password);
				if (currentIndex == -1)
				{
					throw std::invalid_argument("Wrong name, password or/and role.");
				}
				currentUserType = typeUser::thirdParty;
			}
			else
			{
				throw std::invalid_argument("No such role.");
			}
}

void BankingSystem::signup(const MyString& name, const MyString& surname, unsigned EGN, 
	unsigned age, unsigned password, const MyString& role)
{
	if (role == "Client")
	{
		std::cout << "Address:";
		MyString address;
		std::cin >> address;
		std::cout << std::endl;

		clients.add(Client(name, surname, EGN, age, password, address));
		isUsed = true;
		currentIndex = clients.getCount() - 1;
		currentUserType = typeUser::client;
	}
	else if (role == "Employee")
		{
			std::cout << "Bank:";
			MyString bank;
			std::cin >> bank;
			std::cout << std::endl;

			employees.add(Employee(name, surname, EGN, age, password, bank));
			isUsed = true;
			currentIndex = employees.getCount() - 1;
			currentUserType = typeUser::employee;
		}
		else if (role == "ThirdPartyEmployee")
			{
			std::cout << std::endl;
			thirdPartyEmployees.add(ThirdPartyEmployee(name, surname, EGN, age, password));
			isUsed = true;
			currentIndex = thirdPartyEmployees.getCount() - 1;
			currentUserType = typeUser::thirdParty;
			}
			else
			{
				throw std::invalid_argument("No such role.");
			}
}

void BankingSystem::createBank(const MyString& name)
{
	if (checkIfBankExist(name))
	{
		throw std::invalid_argument("A bank with this name already exists.");
	}

	banks.add(name);
}

void BankingSystem::help()const
{
	if (!isUsed)
	{
		throw std::exception("No user.");
	}

	switch (currentUserType)
	{
	case typeUser::client: return clients[currentIndex].help(); break;
	case typeUser::employee: return employees[currentIndex].help(); break;
	case typeUser::thirdParty: return thirdPartyEmployees[currentIndex].help(); break;
	}
}

void BankingSystem::whoami()const
{
	if(!isUsed)
	{
		throw std::exception("No user.");
	}

	switch (currentUserType)
	{
	case typeUser::client: return clients[currentIndex].whoami(); break;
	case typeUser::employee: return employees[currentIndex].whoami(); break;
	case typeUser::thirdParty: return thirdPartyEmployees[currentIndex].whoami(); break;
	}
}

void BankingSystem::exit()
{
	isUsed = false;
}

void BankingSystem::check_avl(const MyString& bankName, unsigned accountNumber)const
{
	if (currentUserType != typeUser::client || isUsed == false)
	{
		throw std::exception("You do not have access to this command");
	}

	if (!checkIfBankExist(bankName))
	{
		throw std::invalid_argument("This bank does not exist.");
	}

	try 
	{
		clients[currentIndex].showAmountInAccount(bankName, accountNumber);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
		throw;
	}
}

void BankingSystem::open(const MyString& bankName)
{
	if (currentUserType != typeUser::client || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}

	if (!checkIfBankExist(bankName))
	{
		throw std::invalid_argument("This bank does not exist.");
	}

	unsigned index = 0;
	try 
	{
		 index = getIndexOfTheLeastBusyEmployee(bankName);
	}
	catch (std::invalid_argument& ia)
	{
		std::cout << ia.what() << std::endl;
		throw;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		throw;
	}

	Person person(clients[currentIndex].getName(), clients[currentIndex].getSurname(), 
		clients[currentIndex].getEGN(), clients[currentIndex].getAge());
	BankAccount bankAccount;
	Task ts(TypeTask::Open, clients[currentIndex].getName() + " wants to open an account.", person, bankName, bankAccount);
	employees[index].addTask(ts);

}

void BankingSystem::close(const MyString& bankName, unsigned account_number)
{
	if (currentUserType != typeUser::client || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}

	if (!checkIfBankExist(bankName))
	{
	throw std::invalid_argument("This bank does not exist.");
	}

	Person person(clients[currentIndex].getName(), clients[currentIndex].getSurname(), 
	clients[currentIndex].getEGN(), clients[currentIndex].getAge());

	BankAccount bankAccount;
	try
	{
	bankAccount = clients[currentIndex].getAccount(account_number);
	}
	catch (std::invalid_argument& ia)
	{
	std::cout << ia.what() << std::endl;
	throw;
	}
	
	unsigned index = 0;
	try
	{
	index = getIndexOfTheLeastBusyEmployee(bankName);
	}
	catch (std::invalid_argument& ia)
	{
	std::cout << ia.what() << std::endl;
	throw;
	}
	catch (std::exception& e)
	{
	std::cout << e.what() << std::endl;
	throw;
	}
	Task ts(TypeTask::Close, clients[currentIndex].getName() + " wants to close their account.", person, bankName, bankAccount);
	employees[index].addTask(ts);
}

void BankingSystem::redeem(const MyString& bankName, unsigned account_number, const MyString& code)
{
	if (currentUserType != typeUser::client || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}

	if (!checkIfBankExist(bankName))
	{
		throw std::invalid_argument("This bank does not exist.");
	}

	int indexCheck = clients[currentIndex].getIndexOfCheck(code);
	if (indexCheck != -1)
	{
		int indexAccount = clients[currentIndex].getIndexOfAccountFromNumber(account_number);
		if (indexAccount == -1)
		{
			throw std::invalid_argument("This account does not exist.");
		}

		clients[currentIndex].cashCheck(indexCheck, indexAccount);
	}
	else
	{
		throw std::invalid_argument("This check does not exist.");
	}
}

void BankingSystem::change(const MyString& newBankName, const MyString& currentBankName, unsigned accountNumber)
{
	if (currentUserType != typeUser::client || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}

	if (!checkIfBankExist(newBankName) || !checkIfBankExist(currentBankName))
	{
		throw std::invalid_argument("The bank does not exist.");
	}

	unsigned index = 0;
	try
	{
		index = getIndexOfTheLeastBusyEmployee(newBankName);
	}
	catch (std::invalid_argument& ia)
	{
		std::cout << ia.what() << std::endl;
		throw;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		throw;
	}

	Person person(clients[currentIndex].getName(), clients[currentIndex].getSurname(), 
		clients[currentIndex].getEGN(), clients[currentIndex].getAge());
	BankAccount bankAccount;
	bankAccount.setAccountNumber(accountNumber);
	Task ts(TypeTask::Change, clients[currentIndex].getName() + " wants to join " + newBankName + ".",
		person, newBankName, bankAccount);
	employees[index].addTask(ts);
}

void BankingSystem::list(const MyString& bankName)const
{
	if (currentUserType != typeUser::client || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}

	if (!checkIfBankExist(bankName))
	{
		throw std::invalid_argument("This bank does not exist.");
	}

	for (int i = 0; i < clients[currentIndex].getCountOfAccounts(); i++)
	{
		if (clients[currentIndex].getNameOfBankAccount(i) == bankName)
		{
			std::cout << clients[currentIndex].getAccountNumberFromIndex(i) << std::endl;
		}
	}
}

void BankingSystem::messages()const
{
	if (currentUserType != typeUser::client || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}
	
	clients[currentIndex].showMessages();
	clients[currentIndex].clearAllMessages();
}

void BankingSystem::tasks()const
{
	if (currentUserType != typeUser::employee || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}

	employees[currentIndex].showAllTasks();
}

void BankingSystem::view(unsigned taskId)const
{
	if (currentUserType != typeUser::employee || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}

	employees[currentIndex].getTask(taskId).viewTask();
}

void BankingSystem::approve(unsigned taskId)
{
	if (currentUserType != typeUser::employee || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}

	int index = getIndexOfClientWithEGN(employees[currentIndex].getTask(taskId).getEGNOfUser());

	if (index == -1)
	{
		throw std::exception("Something went wrong. Thå user does not exist.");
	}

	if (employees[currentIndex].getTask(taskId).getType() == TypeTask::Open)
	{
		unsigned number = getUniqueNumber();
		unsigned balance = employees[currentIndex].getTask(taskId).getAccountAmount();
		MyString bank = employees[currentIndex].getBankName();
		BankAccount ba(number, balance,bank);
		clients[index].addAccount(ba);
		
		MyString accountNumberString = toString(number);
		MyString mess = "You opened an account in" + employees[currentIndex].getBankName() +
			". Your account id is " + accountNumberString + ".";
		clients[index].addMessage(mess);
	}
	else
	{
		if (employees[currentIndex].getTask(taskId).getType() == TypeTask::Close)
		{
			clients[index].closeAccount(employees[currentIndex].getTask(taskId).getAccountNumber());

			MyString mess = "You closed an account in " + employees[currentIndex].getBankName() + ".";
			clients[index].addMessage(mess);
		}
		else
		{
			if (employees[currentIndex].getTask(taskId).getApproved())
			{
				unsigned number = getUniqueNumber();
				MyString accountNumberString = toString(number);
				clients[index].changeAccountBank(employees[currentIndex].getTask(taskId).getAccountNumber(),
					employees[currentIndex].getBankName(), number);
				MyString mess = "You changed your savings account to " + 
					employees[currentIndex].getBankName() +" New account id is " + accountNumberString + ".";
				clients[index].addMessage(mess);
			}
			else
			{
				std::cout << "Cannot proceed - Please make sure " << clients[index].getName() << " is real user." << std::endl;
			}
		}
	}

	employees[currentIndex].removeTask(taskId);
}

void BankingSystem::disapprove(unsigned taskId, const MyString& message)
{
	if (currentUserType != typeUser::employee || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}

	int index = getIndexOfClientWithEGN(employees[currentIndex].getTask(taskId).getEGNOfUser());

	if (index == -1)
	{
		throw std::exception("Something went wrong. Thå user does not exist.");
	}

	clients[index].addMessage(message);
	employees[currentIndex].removeTask(taskId);
}

void BankingSystem::validate(unsigned taskId)
{
	if (currentUserType != typeUser::employee || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}

	int index = getIndexOfClientWithEGN(employees[currentIndex].getTask(taskId).getEGNOfUser());

	if (index == -1)
	{
		throw std::exception("Something went wrong. Thå user does not exist.");
	}

	BankAccount bankAccount;
	try
	{
		bankAccount = clients[index].getAccount(employees[currentIndex].getTask(taskId).getAccountNumber());
	}
	catch (std::invalid_argument& ia)
	{
		std::cout << ia.what() << std::endl;
		throw;
	}

	employees[currentIndex].setAccountBalanceWithIndex(taskId, bankAccount.getAmount());
	employees[currentIndex].changeApproveWithIndex(taskId);
}

void BankingSystem::sendCheck(unsigned sum, const MyString& bankName, unsigned EGN)
{
	if (currentUserType != typeUser::thirdParty || isUsed == false)
	{
		throw std::exception("You do not have access to this command.");
	}

	if (!checkIfBankExist(bankName))
	{
		throw std::invalid_argument("This bank does not exist.");
	}

	int index = getIndexOfClientWithEGN(EGN);
	if (index == -1)
	{
		throw std::invalid_argument("Client with this EGN does not exist.");
	}

	MyString code = getUniqueCode();
	Check check(code, sum);
	clients[index].addCheck(check);
	clients[index].addMessage("You have a check assigned to you by " + thirdPartyEmployees[currentIndex].getName());
}

void BankingSystem::writeToFile() const
{
	std::ofstream ofs("Test.dat", std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::exception("Could not open file.");
	}

	unsigned countClients = clients.getCount();
	ofs.write((const char*)&countClients, sizeof(unsigned));

	for (int i = 0; i < countClients; i++)
	{
		clients[i].writeToFile(ofs);
	}

	unsigned countEmployees = employees.getCount();
	ofs.write((const char*)&countEmployees, sizeof(unsigned));

	for (int i = 0; i < countEmployees; i++)
	{
		employees[i].writeToFile(ofs);
	}

	unsigned countThirdParty = thirdPartyEmployees.getCount();
	ofs.write((const char*)&countThirdParty, sizeof(unsigned));

	for (int i = 0; i < countThirdParty; i++)
	{
		thirdPartyEmployees[i].writeToFile(ofs);
	}

	unsigned countBanks= banks.getCount();
	ofs.write((const char*)&countBanks, sizeof(unsigned));

	for (int i = 0; i < countBanks; i++)
	{
		writeStringToFile(ofs,banks[i].c_str());
	}

	ofs.clear();
	ofs.close();
}

void BankingSystem::readFromFiLe()
{
	std::ifstream ifs("Test.dat", std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::exception("Could not open file.");
	}

	unsigned countClients = 0;
	ifs.read((char*)&countClients, sizeof(unsigned));

	for (int i = 0; i < countClients; i++)
	{
		Client cl;
		cl.readFromFiLe(ifs);
		clients.add(cl);
	}

	unsigned countEmployees = 0;
	ifs.read((char*)&countEmployees, sizeof(unsigned));

	for (int i = 0; i < countEmployees; i++)
	{
		Employee em;
		em.readFromFiLe(ifs);
		employees.add(em);
	}

	unsigned countThirdPartys = 0;
	ifs.read((char*)&countThirdPartys, sizeof(unsigned));

	for (int i = 0; i < countThirdPartys; i++)
	{
		ThirdPartyEmployee tpe;
		tpe.readFromFiLe(ifs);
		thirdPartyEmployees.add(tpe);
	}

	unsigned countBanks = 0;
	ifs.read((char*)&countBanks, sizeof(unsigned));

	for (int i = 0; i < countBanks; i++)
	{
		MyString bank = readStringFromFile(ifs);
		banks.add(bank);
	}

	ifs.clear();
	ifs.close();
}

bool BankingSystem::checkIfBankExist(const MyString& bankName)const
{
	for (int i = 0; i < banks.getCount(); i++)
	{
		if (bankName == banks[i])
		{
			return true;
		}
	}

	return false;
}

unsigned BankingSystem::getIndexOfTheLeastBusyEmployee(const MyString& bankName)const
{
	if (!checkIfBankExist(bankName))
	{
		throw std::invalid_argument("This bank does not exist.");
	}

	unsigned currentMinIndex = -1;
	unsigned currentMinCount = MAX_TASKS;
	for (int i = 0; i < employees.getCount(); i++)
	{
		if (employees[i].getBankName() == bankName && employees[i].getTasksCount() < currentMinCount)
		{
			currentMinIndex = i;
			currentMinCount = employees[i].getTasksCount();
		}
	}

	if (currentIndex != -1)
	{
		return currentIndex;
	}
	else
	{
		throw std::exception("The bank does not have employees.");
	}
}

int BankingSystem::getIndexOfEmployee(const MyString& name, unsigned password)const
{
	for (int i = 0; i < employees.getCount(); i++)
	{
		if (employees[i].getName() == name && employees[i].getPassword() == password)
		{
			return i;
		}
	}

	return -1;
}

int BankingSystem::getIndexOfClient(const MyString& name, unsigned password)const
{
	for (int i = 0; i < clients.getCount(); i++)
	{
		if (clients[i].getName() == name && clients[i].getPassword() == password)
		{
			return i;
		}
	}

	return -1;
}

int BankingSystem::getIndexOfThirdPartyEmployees(const MyString& name, unsigned password)const
{
	for (int i = 0; i < thirdPartyEmployees.getCount(); i++)
	{
		if (thirdPartyEmployees[i].getName() == name && thirdPartyEmployees[i].getPassword() == password)
		{
			return i;
		}
	}

	return -1;
}

int BankingSystem::getIndexOfClientWithEGN(unsigned EGN)const
{
	for (int i = 0; i < clients.getCount(); i++)
	{
		if (clients[i].getEGN() == EGN)
		{
			return i;
		}
	}

	return -1;
}

bool BankingSystem::checkIfAccountNumberIsUnique(unsigned number)const
{
	for (int i = 0; i < clients.getCount(); i++)
	{
		if (!clients[i].checkIfAccountNumberIsUniqueForPerson(number))
		{
			return false;
		}
	}

	return true;
}

unsigned BankingSystem::getUniqueNumber()const
{
	unsigned number;
	do
	{
		number = randomNumber();
	} while (!checkIfAccountNumberIsUnique(number));

	return number;
}

const MyString& BankingSystem::getUniqueCode()const
{
	MyString code;
	do
	{
		code = generateCode();
	} while (!checkIfCodeIsUnique(code));

	return code;
}

bool BankingSystem::checkIfCodeIsUnique(const MyString& code)const
{
	for (int i = 0; i < clients.getCount(); i++)
	{
		if (!clients[i].checkIfCodeIsUniqueForPerson(code))
		{
			return false;
		}
	}

	return true;
}
