#pragma once
#include "ChequePool.h"
#include "User.h"
class ThirdPartyEmployee : public User
{

public:
	ThirdPartyEmployee() = default;
	ThirdPartyEmployee(const MyString& name, const MyString& id, size_t age, MyString password);
	//sends msessege to the user
	const ChequeCode& make_check(size_t sum, const char* verificationCode);

	void saveToFile(std::ofstream& ofs);
	void readFromFile(std::ifstream& ifs);
private:
	static ChequePool checks;

};
