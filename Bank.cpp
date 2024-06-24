#include "Bank.h"


size_t Bank::findEmployeeIndxForTask() const
{
	if (employees.isEmpty())
	{
		MyString e = "No employees in bank " + name;
		throw std::runtime_error(e.c_str());
	}
	size_t indx = 0;
	size_t leastTasks = employees[0].getTasksCount();
	for (int i = 1; i < employees.getSize(); i++)
	{
		if (leastTasks > employees[i].getTasksCount())
		{
			leastTasks = employees[i].getTasksCount();
			indx = i;
		}
	}
	return indx;
}

Bank::Bank(const MyString& name)
{
	this->name = name;
}

const MyString& Bank::getName() const
{
	return name;
}

Employee* Bank::getEmployee(size_t indx)
{
	if (indx < 0 || indx >= employees.getSize())
	{
		throw std::runtime_error("Out of bounds");
	}
	return &employees[indx];
}

size_t Bank::searchEmployee(const MyString& name, const MyString& password)
{
	for (int i = 0; i < employees.getSize(); i++)
	{
		if (employees[i].isValidUser(name, password))
		{
			return i;
		}
	}
	return -1;
}

void Bank::addEmployee(const Employee& employee)
{
	employees.pushBack(employee);
}
void Bank::addEmployee(Employee&& employee)
{
	employees.pushBack(std::move(employee));
}

void Bank::addAccount(const Account& acc)
{
	accounts.pushBack(acc);
}

void Bank::addAccount(Account&& acc)
{
	accounts.pushBack(std::move(acc));
}

size_t Bank::getAccIndx(size_t accId) const
{
	for (int i = 0; i < accounts.getSize(); i++)
	{
		if (accounts[i].getAccId() == accId)
		{
			return i;
		}
	}
	return -1;
}

void Bank::checkAvailability(size_t accId) const
{
	size_t accIndx = getAccIndx(accId);
	accounts[accIndx].checkAvailability();
}

void Bank::removeAccount(size_t indx)
{
	accounts.popAt(indx);
}

void Bank::giveTask(Task* task)
{
	size_t indx = findEmployeeIndxForTask();
	employees[indx].addTask(task);
}
Account& Bank::getAccount(size_t accId)
{
	size_t accIndx = getAccIndx(accId);
	return accounts[accIndx];
}
void Bank::list(const MyString& userId) const
{
	for (int i = 0; i < accounts.getSize(); i++)
	{
		if (accounts[i].getUserId() == userId)
		{
			std::cout << "* " << accounts[i].getAccId() << std::endl;
		}
	}
}



void Bank::saveToFile(std::ofstream& ofs)
{
	name.saveToFile(ofs);

	size_t count = accounts.getSize();

	ofs.write((const char*)(&count), sizeof(count));

	for (int i = 0; i < count; i++)
	{
		accounts[i].saveToFile(ofs);
	}

	count = employees.getSize();
	ofs.write((const char*)(&count), sizeof(count));
	for (int i = 0; i < employees.getSize(); i++)
	{
		employees[i].saveToFile(ofs);
	}
}

void Bank::readFromFile(std::ifstream& ifs)
{
	name.readFromFile(ifs);
	size_t count;

	ifs.read((char*)&count, sizeof(size_t));
	for (int i = 0; i < count; i++)
	{
		Account acc;
		acc.readFromFile(ifs);
		accounts.pushBack(acc);
	}
	ifs.read((char*)(&count), sizeof(count));
	for (int i = 0; i < count; i++)
	{
		Employee employee;
		employee.readFromFile(ifs);
		employees.pushBack(employee);
	}
}
