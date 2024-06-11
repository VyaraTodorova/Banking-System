#pragma once
#include "Account.h"
class Client : public Account
{
public:
	unsigned check_avl()const;
	void whoami() const override;
	void help() const override;
private:

};

