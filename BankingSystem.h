#pragma once
#include "PolymorficPtr.hpp"
#include "Client.h"

class BankingSystem
{
public:
	void login();
	void signup();
	void createBank();

private:
	Polymorphic_Ptr<Client> clients;

};

