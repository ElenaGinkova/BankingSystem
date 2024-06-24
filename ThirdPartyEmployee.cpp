#include "ThirdPartyEmployee.h"

ChequePool ThirdPartyEmployee::checks;
ThirdPartyEmployee::ThirdPartyEmployee(const MyString& name, const MyString& id, size_t age, MyString password) : User(name, id,age,password)
{
}

const ChequeCode& ThirdPartyEmployee::make_check(size_t sum, const char* code)
{
	return checks.getAllocatedCode(code, sum);
}

void ThirdPartyEmployee::saveToFile(std::ofstream& ofs)
{
	data.saveToFile(ofs);
}

void ThirdPartyEmployee::readFromFile(std::ifstream& ifs)
{
	data.readFromFile(ifs);
}
