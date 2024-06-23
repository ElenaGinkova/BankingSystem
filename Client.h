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
	Task* close(Account* acc);
	Task* change(const MyString& , const MyString& , Account* acc);
	void printMesseges() const;
	void redeem(const MyString& verificationCode);//
	void recieveCheque(const ChequeCode& code);
	const MyString& getUserId() const;
	void recieveMessage(const MyString& message);
	void checkAvailabilty(Account* acc) const;
private:
	Vector<MyString> messeges;
	Vector<ChequeCode> cheques;	
};
