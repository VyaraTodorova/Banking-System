#include "BankingSystem.h"

void BankingSystem::login()
{
	std::cout << "Name:";
	MyString name;
	std::cin >> name;

	std::cout << "Role:";
	MyString role;
	std::cin >> role;

	std::cout << "Password:";
	unsigned password;
	std::cin >> password;
	std::cout << std::endl;

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
	else {
		if (role == "Employee")
		{
			isUsed = true;
			currentIndex = getIndexOfEmployee(name, password);
			if (currentIndex == -1)
			{
				throw std::invalid_argument("Wrong name, password or/and role.");
			}
			currentUserType = typeUser::employee;
		}
		else {
			if (role == "Third-party employee")
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
	}
}

void BankingSystem::signup()
{
	std::cout << "Name:";
	MyString name;
	std::cin >> name;

	std::cout << "Surname:";
	MyString surname;
	std::cin >> surname;

	std::cout << "EGN:";
	unsigned EGN;
	std::cin >> EGN;

	std::cout << "Age:";
	unsigned age;
	std::cin >> age;

	std::cout << "Password:";
	unsigned password;
	std::cin >> password;

	std::cout << "Role:";
	MyString role;
	std::cin >> role;

	if (role == "Client")
	{
		std::cout << "Address:";
		MyString address;
		std::cin >> address;
		std::cout << std::endl;

		clients.add(*new Client(name, surname, EGN, age, password, address));
		isUsed = true;
		currentIndex = clients.getCount() - 1;
		currentUserType = typeUser::client;
	}
	else {
		if (role == "Employee")
		{
			std::cout << "Bank:";
			MyString bank;
			std::cin >> bank;
			std::cout << std::endl;

			employees.add(*new Employee(name, surname, EGN, age, password, bank));
			isUsed = true;
			currentIndex = employees.getCount() - 1;
			currentUserType = typeUser::employee;
		}
		else {
			if (role == "Third-party employee")
			{
			std::cout << std::endl;
			thirdPartyEmployees.add(*new ThirdPartyEmployee(name, surname, EGN, age, password));
			isUsed = true;
			currentIndex = thirdPartyEmployees.getCount() - 1;
			currentUserType = typeUser::thirdParty;
			}
			else
			{
				throw std::invalid_argument("No such role.");
			}
		}
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
		throw std::exception("You do not have access to this command");
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

	Person person(clients[currentIndex].getName(), clients[currentIndex].getSurname(), clients[currentIndex].getEGN(), clients[currentIndex].getAge());
	BankAccount bankAccount;
	employees[index].addTask(bankName, person, TypeTask::Open, clients[currentIndex].getName() + "wants to open an account", bankAccount);
	

}

void BankingSystem::close(const MyString& bankName, unsigned account_number)
{
	if (currentUserType != typeUser::client || isUsed == false)
	{
		throw std::exception("You do not have access to this command");
	}

if (!checkIfBankExist(bankName))
{
	throw std::invalid_argument("This bank does not exist.");
}

Person person(clients[currentIndex].getName(), clients[currentIndex].getSurname(), clients[currentIndex].getEGN(), clients[currentIndex].getAge());
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

employees[index].addTask(bankName, person, TypeTask::Close, clients[currentIndex].getName() + "wants to close their account.", bankAccount);
}

void BankingSystem::redeem(const MyString& bankName, unsigned account_number, const MyString& code)
{

}

void BankingSystem::change(const MyString& newBankName, const MyString& currentBankName, unsigned account_number)
{
	if (currentUserType != typeUser::client || isUsed == false)
	{
		throw std::exception("You do not have access to this command");
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

	Person person(clients[currentIndex].getName(), clients[currentIndex].getSurname(), clients[currentIndex].getEGN(), clients[currentIndex].getAge());
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

	employees[index].addTask(newBankName, person, TypeTask::Change, clients[currentIndex].getName() + "wants to join " + newBankName, bankAccount);
}

void BankingSystem::list(const MyString& bankName)const
{
	if (currentUserType != typeUser::client || isUsed == false)
	{
		throw std::exception("You do not have access to this command");
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
		throw std::exception("You do not have access to this command");
	}
	
	clients[currentIndex].showMessages();
}

void BankingSystem::tasks()const
{
	if (currentUserType != typeUser::employee || isUsed == false)
	{
		throw std::exception("You do not have access to this command");
	}

	employees[currentIndex].showAllTasks();
}

void BankingSystem::view(unsigned taskId)const
{
	if (currentUserType != typeUser::employee || isUsed == false)
	{
		throw std::exception("You do not have access to this command");
	}

	employees[currentIndex].getTask(taskId).viewTask();
}

void BankingSystem::approve(unsigned taskId)
{
	if (currentUserType != typeUser::employee || isUsed == false)
	{
		throw std::exception("You do not have access to this command");
	}

	if (employees[currentIndex].getTask(taskId).getType() == TypeTask::Open)
	{
		int index = getIndexOfClientWithEGN(employees[currentIndex].getTask(taskId).getEGNOfUser());

		if (index == 1)
		{
			throw std::exception("Something went wrong. Thå user does not exist.");
		}

		unsigned number = 0;
		std::cout << "Set account number: ";
		std::cin >> number;

		clients[index].addAccount(number, employees[currentIndex].getTask(taskId).getAccountAmount(), employees[currentIndex].getTask(taskId).getBankName());
		employees[currentIndex].removeTask(taskId);
		/*MyString mess = "You opened an account in" + employees[currentIndex].getTask(taskId).getBankName() +
			". Your account id is " + number + ".";
		clients[index].addMessage()*/
	}
	//is not ready!!!!!
}

void BankingSystem::disapprove(unsigned taskId, const MyString& message)
{
	if (currentUserType != typeUser::employee || isUsed == false)
	{
		throw std::exception("You do not have access to this command");
	}
}

bool BankingSystem::validate(unsigned taskId)
{
	if (currentUserType != typeUser::employee || isUsed == false)
	{
		throw std::exception("You do not have access to this command");
	}

	return true;
}

void BankingSystem::sendCheck(unsigned sum, const MyString& bankName, unsigned EGN)
{
	if (currentUserType != typeUser::thirdParty || isUsed == false)
	{
		throw std::exception("You do not have access to this command");
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

	MyString code;
	Check check(code, sum);
	clients[index].addCheck(check);
	clients[index].addMessage("You have a check assigned to you by " + thirdPartyEmployees[currentIndex].getName());
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

