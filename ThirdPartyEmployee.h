#pragma once
#include "User.h"
class ThirdPartyEmployee : public User
{
	
public:
	ThirdPartyEmployee();
	ThirdPartyEmployee(const MyString& name, const MyString& surname, unsigned EGN, unsigned age, unsigned password);

	const typeUser& getTypeOfUser()const override;
	void help()const override;
	void whoami()const override;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFiLe(std::ifstream& ifs);
};


