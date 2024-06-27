#pragma once
#include "Vector.hpp"
#include "MyString.h"
#include "Account.h"
#include "Employee.h"

//generates tasks for employees when client asks
class Bank
{
public:
	Bank() = default;
	Bank(const MyString& name);
	const MyString& getName() const;
	Employee* getEmployee(size_t indx);
	size_t searchEmployee(const MyString& name, const MyString& password);

	void addEmployee(const Employee&);
	void addEmployee(Employee&&);
	void addAccount(const Account&);
	void addAccount(Account&&);
	size_t getAccIndx(size_t accId) const;
	void checkAvailability(size_t accId)const;
	void removeAccount(size_t indx);
	void giveTask(Task*);
	Account& getAccount(size_t accId);
	void list(const MyString& userId) const;

	
	void saveToFile(std::ofstream& ofs);
	void readFromFile(std::ifstream& ifs);
private:
	MyString name;
	Vector<Account> accounts;
	Vector<Employee> employees;
	
	size_t findEmployeeIndxForTask() const;
};
