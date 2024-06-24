#pragma once
#include <iostream>
#include "MyString.h"
class Account
{
public:
	Account() = default;
	Account(const MyString& bankName, const MyString& userId);
	void addMoney(double amount);
	void checkAvailability() const;
	void printInfo() const;
	void changeBank(const MyString& bankName);
	size_t getAccId()const;
	const MyString& getBankName() const;
	const MyString& getUserId() const;

	
	void saveToFile(std::ofstream& ofs);
	void readFromFile(std::ifstream& ifs);
	static size_t ID_NUM;
private:
	size_t accId = 0;//account id
	MyString userId;
	MyString bankName;
	double balance = 0;
};

