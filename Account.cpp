#include "Account.h"

 size_t Account::ID_NUM = 0;

Account::Account(const MyString& bankName, const MyString& userId) : bankName(bankName), userId(userId)
{
	accId = ID_NUM++;
}

void Account::addMoney(double amount)
{
	balance += amount;
}

void Account::checkAvailability() const
{
	std::cout << balance << '$';
}

void Account::printInfo() const
{
	std::cout << "Bank: " << bankName << "\nAccount number: " << accId << "\nBalance: " << balance << "$\n";
}

void Account::changeBank(const MyString& bankName)
{
	this->bankName = bankName;
}

size_t Account::getAccId() const
{
	return accId;
}

const MyString& Account::getBankName() const
{
	return bankName;
}

const MyString& Account::getUserId() const
{
	return userId;
}


void Account::saveToFile(std::ofstream& ofs)
{
	ofs.write((const char*)&accId, sizeof(accId));
	userId.saveToFile(ofs);
	bankName.saveToFile(ofs);
	ofs.write((const char*)&balance, sizeof(balance));
}

void Account::readFromFile(std::ifstream& ifs)
{
	ifs.read((char*)&accId, sizeof(accId));
	userId.readFromFile(ifs);
	bankName.readFromFile(ifs);
	ifs.read((char*)&balance, sizeof(balance));
}

