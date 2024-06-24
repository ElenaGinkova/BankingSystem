#pragma once
#include <iostream>
#include "Bank.h"
#include "Client.h"
#include "ThirdPartyEmployee.h"

enum class UserType
{
	UndefinedType,
	ClientType,
	EmployeeType,
	ThridPartyEmployeeType
};

class BankSystem
{
public:
	void logIn();
	void signUp();
	void createBank();
	void logOut();

	User* getLoggedIn() const;
	UserType getUserType() const;
	Client* getClient(const MyString& userId);
	Bank* findBank(MyString);

	void saveToFile();
	void readFromFile();
private:
	struct LoggedData
	{
		User* loggedIn = nullptr;
		UserType type = UserType::UndefinedType;
	};

	LoggedData loggedUser;
	Vector<Bank> banks;
	Vector<Client> clients;
	Vector<ThirdPartyEmployee> thirdPartyEmployees;


	void addClient(const MyString& name, const MyString& id, size_t age);
	void addEmployee(const MyString& name, const MyString& id, size_t age);
	void addThirdPartyEmployee(const MyString& name, const MyString& id, size_t age);

	void readFromConsole(MyString& name, MyString& id, size_t& age, MyString& role);

	bool logInUser(const MyString& name, const MyString& password);
	bool logInClient(const MyString& name, const MyString& password);
	bool logInBanker(const MyString& name, const MyString& password);
	bool logInThirdPartyEmployee(const MyString& name, const MyString& password);

	void checkForUsedId(const MyString& id);
	void checkForUsedLogin(const MyString& name, const MyString& pass);
	bool checkForExistingBank(const MyString& name);
};
