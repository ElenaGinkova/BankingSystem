#pragma once
#include "BankSystem.h"
class EmployeeRunner
{
public:
	EmployeeRunner(BankSystem& system);
	void runEmployee();
	void approve();
	void disapprove();
	void validateChange();
	void help() const;

private:
	BankSystem& system;
	Employee* employee = nullptr;

	void approveChange(size_t taskNum);
	void approveOpen(size_t taskNum);
	void approveClose(size_t taskNum);

	Client& getClient(Task* task) const;
	void sendCustomMessage(MyString mess, Client& client, size_t taskNum);
	void changeBanks(const MyString&, const MyString&, size_t accIndx, Account& acc);


	void getCustomMessage(MyString& message);
	static const size_t MAX_BUFF_SIZE;
	int taskIndex();
};
