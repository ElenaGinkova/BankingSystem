#pragma once
#include "ThirdPartyEmployeeRunner.h"
#include "BankSystem.h"
class ThirdPartyEmployeeRunner
{
public:
	ThirdPartyEmployeeRunner(BankSystem& system);

	void runThirdPartyEmployee();
private:
	BankSystem& system;

	void help() const;
	void sendCheque();
};

