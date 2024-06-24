#pragma once
#include "User.h"
#include "Account.h"
#include "OpenTask.h"
#include "CloseTask.h"
#include "ChangeTask.h"
#include "Cheque.h"
#include <iostream>

class Client : public User
{
public:
	Client() = default;
	Client(const MyString& name, const MyString& id, size_t age, MyString password);

	Task* open();
	Task* close(Account& acc);
	Task* change(const MyString& , const MyString& , Account& acc);
	void printMesseges() const;
	const ChequeCode& getCheque(const MyString& verificationCode)const;
	void redeemCheque(const MyString& verificationCode);
	void recieveCheque(const ChequeCode& code);
	const MyString& getUserId() const;
	void recieveMessage(const MyString& message);
	void checkAvailabilty(Account* acc) const;

	void saveToFile(std::ofstream& ofs);
	void readFromFile(std::ifstream& ifs);
private:
	int findChequeInd(const MyString& verificationCode)const;

	Vector<MyString> messeges;
	Vector<ChequeCode> cheques;	
};
