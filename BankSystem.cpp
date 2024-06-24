#include "BankSystem.h"

User* BankSystem::getLoggedIn() const
{
	return loggedUser.loggedIn;
}

UserType BankSystem::getUserType() const
{
	return loggedUser.type;
}

void BankSystem::logOut()
{
	loggedUser.loggedIn = nullptr;
	loggedUser.type = UserType::UndefinedType;
}

void BankSystem::logIn()
{
	MyString name, password;
	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "Passowrd: ";
	std::cin >> password;
	if (!logInUser(name, password))
	{
		std::cout << "Incorrect name or password!";
	}
}

void BankSystem::signUp()
{
	MyString name, role, password;
	MyString id;
	size_t age = 0;
	readFromConsole(name, id, age, role);
	try {
		checkForUsedId(id);
	
		if (role == "Employee")
		{
			addEmployee(name, id, age);
		}
		else if (role == "Client")
		{
			addClient(name, id, age);
		}
		else if (role == "Third-party-employee")
		{
			addThirdPartyEmployee(name, id, age);
		}
		else
		{
			throw std::runtime_error("Incorrect role!");
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

void BankSystem::createBank()
{
	MyString name;
	std::cin >> name;
	if (checkForExistingBank(name))
	{
		std::cout << "Bank exists!";
		return;
	}
	Bank bank(name);
	banks.pushBack(bank);
}

Bank* BankSystem::findBank(MyString bankAssociated)
{
	for (int i = 0; i < banks.getSize(); i++)
	{
		if (banks[i].getName() == bankAssociated)
		{
			return &banks[i];
		}
	}
	throw std::runtime_error("There is no such bank!");
}

Client* BankSystem::getClient(const MyString& userId)
{
	for (int i = 0; i < clients.getSize(); i++)
	{
		if (clients[i].getUserId() == userId)
		{
			return &clients[i];
		}
	}
	throw std::logic_error("No such client!");
}

void BankSystem::addClient(const MyString& name, const MyString& id, size_t age)
{
	MyString password;
	std::cout << "Password: ";
	std::cin >> password;
	Client client(name, id, age, password);
	clients.pushBack(client);
}

void BankSystem::addEmployee(const MyString& name, const MyString& id, size_t age)
{
	MyString bankAssociated;
	std::cout << "Bank associated: ";
	std::cin >> bankAssociated;
	Bank* bank = findBank(bankAssociated);
	MyString password;
	std::cout << "Password: ";
	std::cin >> password;
	checkForUsedLogin(name, password);
	Employee employee(name, id, age, password, bankAssociated);
	bank->addEmployee(employee);
}

void BankSystem::addThirdPartyEmployee(const MyString& name, const MyString& id, size_t age)
{
	MyString password;
	std::cout << "Password: ";
	std::cin >> password;
	checkForUsedLogin(name, password);
	ThirdPartyEmployee employee(name, id, age, password);
	thirdPartyEmployees.pushBack(employee);
}

void BankSystem::readFromConsole(MyString& name, MyString& id, size_t& age, MyString& role)
{
	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "EGN: ";
	std::cin >> id;
	std::cout << "Age: ";
	std::cin >> age;
	std::cout << "Role: ";
	std::cin >> role;
}

bool BankSystem::logInUser(const MyString& name, const MyString& password)
{
	if (logInClient(name, password))
	{
		return true;
	}
	else if (logInBanker(name, password))
	{
		return true;
	}
	else if (logInThirdPartyEmployee(name, password))
	{
		return true;
	}
	return false;
}

bool BankSystem::logInClient(const MyString& name, const MyString& password)
{
	for (int i = 0; i < clients.getSize(); i++)
	{
		if (clients[i].isValidUser(name, password))
		{
			loggedUser.loggedIn = &clients[i];
			loggedUser.type = UserType::ClientType;
			return true;
		}
	}
	return false;
}

bool BankSystem::logInBanker(const MyString& name, const MyString& password)
{
	for (int i = 0; i < banks.getSize(); i++)
	{
		int indx = -1;
		indx = banks[i].searchEmployee(name, password);
		if(indx != -1)
		{
			loggedUser.loggedIn = banks[i].getEmployee(indx);
			loggedUser.type = UserType::EmployeeType;
			return true;
		}
	}
	return false;
}

bool BankSystem::logInThirdPartyEmployee(const MyString& name, const MyString& password)
{
	for (int i = 0; i < thirdPartyEmployees.getSize(); i++)
	{
		if (thirdPartyEmployees[i].isValidUser(name, password))
		{
			loggedUser.loggedIn = &thirdPartyEmployees[i];
			loggedUser.type = UserType::ThridPartyEmployeeType;
			return true;
		}
	}
	return false;
}

//needed for clients
void BankSystem::checkForUsedId(const MyString& id)
{
	for (int i = 0; i < clients.getSize(); i++)
	{
		if (clients[i].getUserId() == id)
		{
			throw std::runtime_error("Client with this id exists");
		}
	}
}

//needed because users login with name and password
void BankSystem::checkForUsedLogin(const MyString& name, const MyString& pass)
{
	if (logInUser(name, pass))
	{
		logOut();
		throw std::runtime_error("Use other password!");
	}
}

bool BankSystem::checkForExistingBank(const MyString& name)
{
	for (int i = 0; i < banks.getSize(); i++)
	{
		if (banks[i].getName() == name)
		{
			return true;
		}
	}
	return false;
}

void BankSystem::saveToFile()
{
	MyString fileName("BankSystem.dat");
	std::ofstream ofs(fileName.c_str(), std::ios::binary);
	if (!ofs.is_open())
	{
		return;
	}
	size_t size = banks.getSize();
	ofs.write((const char*)(&size), sizeof(size));
	for (int i = 0; i < banks.getSize(); i++)
	{
		banks[i].saveToFile(ofs);
	}
	size = clients.getSize();
	ofs.write((const char*)(&size), sizeof(size_t));
	for (int i = 0; i < clients.getSize(); i++)
	{
		clients[i].saveToFile(ofs);
	}
	size = thirdPartyEmployees.getSize();
	ofs.write((const char*)(&size), sizeof(size_t));
	for (int i = 0; i < thirdPartyEmployees.getSize(); i++)
	{
		thirdPartyEmployees[i].saveToFile(ofs);
	}
	ofs.write((const char*)(&Account::ID_NUM), sizeof(Account::ID_NUM));
	ofs.flush();
	ofs.close();
}

void BankSystem::readFromFile()
{
	MyString fileName("BankSystem.dat");
	std::ifstream ifs(fileName.c_str(), std::ios::binary);
	if (!ifs.is_open())
	{
		return;
	}
	size_t size = 0;
	ifs.read((char*)&size, sizeof(size));
	
	for (int i = 0; i < size; i++)
	{
		Bank bank;
		bank.readFromFile(ifs);
		banks.pushBack(bank);
	}
	
	ifs.read((char*)&size, sizeof(size));
	for (int i = 0; i < size; i++)
	{
		Client client;
		client.readFromFile(ifs);
		clients.pushBack(client);
	}
	ifs.read((char*)&size, sizeof(size));
	for (int i = 0; i < size; i++)
	{
		ThirdPartyEmployee thirdPartyEmployee;
		thirdPartyEmployee.readFromFile(ifs);
		thirdPartyEmployees.pushBack(thirdPartyEmployee);
	}
	ifs.read((char*)(&Account::ID_NUM), sizeof(Account::ID_NUM));
	ifs.close();
}

