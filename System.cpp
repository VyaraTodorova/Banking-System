#include "System.h"
#include "BankingSystem.h"

void run()
{
	BankingSystem bs;
	//bs.readFromFiLe();
	MyString command;
	while (true)
	{
		std::cout << "Command:";
		std::cin >> command;
		if (command == "signup")
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

			bs.signup(name, surname, EGN, age, password, role);
			
			std::cout << "The user is create." << std::endl;
		}
		else if (command == "login")
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

			bs.login(name, password, role);
			std::cout << "You are loged in." << std::endl;
		}
		else if (command == "createBank")
		{
			std::cout << "Bank name:";
			MyString bankName;
			std::cin >> bankName;

			bs.createBank(bankName);
			std::cout << "Bank created." << std::endl;
		}
		else if (command == "help")
		{
			bs.help();
		}
		else if (command == "whoami")
		{
			bs.whoami();
		}
		else if (command == "exit")
		{
			bs.exit();
			std::cout << "Exited." << std::endl;
		}
		else if (command == "quit_system")
		{
			bs.exit();
			break;
		}
		else if (command == "check_avl")
		{
			std::cout << "Bank name:";
			MyString bankName;
			std::cin >> bankName;

			std::cout << "Account Number:";
			unsigned accountNumber;
			std::cin >> accountNumber;

			bs.check_avl(bankName, accountNumber);
		}
		else if (command == "open")
		{
			std::cout << "Bank name:";
			MyString bankName;
			std::cin >> bankName;

			bs.open(bankName);
		}
		else if (command == "close")
		{
			std::cout << "Bank name:";
			MyString bankName;
			std::cin >> bankName;

			std::cout << "Account Number:";
			unsigned accountNumber;
			std::cin >> accountNumber;

			bs.close(bankName, accountNumber);
		}
		else if (command == "redeem")
		{
			std::cout << "Bank name:";
			MyString bankName;
			std::cin >> bankName;

			std::cout << "Account Number:";
			unsigned accountNumber;
			std::cin >> accountNumber;

			std::cout << "Code:";
			MyString code;
			std::cin >> code;
			bs.redeem(bankName, accountNumber, code);
		}
		else if (command == "change")
		{
			std::cout << "New bank name:";
			MyString newBankName;
			std::cin >> newBankName;

			std::cout << "Current bank name:";
			MyString currentBankName;
			std::cin >> currentBankName;

			std::cout << "Account Number:";
			unsigned accountNumber;
			std::cin >> accountNumber;

			bs.change(newBankName, currentBankName, accountNumber);
		}
		else if (command == "list")
		{
			std::cout << "Bank name:";
			MyString bankName;
			std::cin >> bankName;

			bs.list(bankName);
		}
		else if (command == "messages")
		{
			bs.messages();
		}
		else if (command == "tasks")
		{
			bs.tasks();
		}
		else if (command == "view")
		{
			std::cout << "TaskId:";
			unsigned taskId;
			std::cin >> taskId;

			bs.view(taskId);
		}
		else if (command == "approve")
		{
			std::cout << "TaskId:";
			unsigned taskId;
			std::cin >> taskId;

			bs.approve(taskId);
		}
		else if (command == "disapprove")
		{
			std::cout << "TaskId:";
			unsigned taskId;
			std::cin >> taskId;

			std::cout << "Message:";
			MyString mess;
			std::cin >> mess;

			bs.disapprove(taskId,mess);
		}
		else if (command == "validate")
		{
			std::cout << "TaskId:";
			unsigned taskId;
			std::cin >> taskId;

			bs.validate(taskId);
		}
		else if (command == "sendCheck")
		{
			std::cout << "Sum:";
			unsigned sum;
			std::cin >> sum;

			std::cout << "Bank name:";
			MyString bankName;
			std::cin >> bankName;

			std::cout << "EGN:";
			unsigned EGN;
			std::cin >> EGN;

			bs.sendCheck(sum, bankName, EGN);
			std::cout << "Check is send." << std::endl;
		}
		else
		{
			throw std::invalid_argument("This command is invalid.");
		}
	}
}

