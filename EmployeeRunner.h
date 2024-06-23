#pragma once
#include "BankSystem.h"
class EmployeeRunner
{
public:
	EmployeeRunner(BankSystem& system);
	void runEmployee();
	void approve(Employee& employee);
	void disapprove(Employee& employee);
	void validateChange(Employee& employee);
	void help() const;

private:
	BankSystem& system;

	void approveChange(Employee& employee, size_t taskNum);
	void approveOpen(Employee& employee, size_t taskNum);
	void approveClose(Employee& employee, size_t taskNum);

	Client& getClient(Task* task) const;
	void sendCustomMessage(MyString mess, Client& client, Employee& employee, size_t taskNum);
	void changeBanks(const MyString&, const MyString&, size_t accIndx, Account* acc);


	void getCustomMessage(MyString& message);
	static const size_t MAX_BUFF_SIZE;
};

//excecute, send messege, pop 
