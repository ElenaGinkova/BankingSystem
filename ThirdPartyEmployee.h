#pragma once
#include "ChequePool.h"
#include "User.h"
class ThirdPartyEmployee : public User
{
private:
	static ChequePool checks;

public:
	ThirdPartyEmployee(MyString name, size_t id, size_t age, MyString password);
	//sends msessege to the user
	void send_check(size_t sum, char* verificationCode, size_t id);
};