#pragma once
#include "User.h"
#include "Account.h"

class Client : public User
{
private:
	Vector<MyString> messeges;
	Vector<Account*> accounts;
	Vector<ChequeCode> cheque;//*?

public:
	//and checks
	Client(MyString name, size_t id, size_t age, MyString password);

	void checkAvailabilty(const char* bankName, size_t accountNum) const;
	void open(const char* bankName, size_t accountNum);
	void close(const char* bankName, size_t accountNum);
	void redeem(const char* bankName, size_t accountNum, const char* verificationCode);
	void change(const char* newBank, const char* currentBank, size_t accountNum);
	void list(const char* bankName) const;
	void printMesseges() const;
	
};


//-add big 6 because of using pointers in vector