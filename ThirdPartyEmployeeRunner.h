#pragma once
#include "Runner.h"
#include "ThirdPartyEmployeeRunner.h"
#include "BankSystem.h"
class ThirdPartyEmployeeRunner : public Runner
{
public:
	ThirdPartyEmployeeRunner(BankSystem& system);

	void run() override;
private:
	BankSystem& system;

	void help() const;
	void sendCheque();
};

