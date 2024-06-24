#pragma once
#include "BankSystem.h"
class ClientRunner
{
public:
	ClientRunner(BankSystem& system);

	void runClient();
private:
	BankSystem& system;
	Client* client = nullptr;

	void fromConsole(MyString&, int&);
	void checkAvailability();
	void open();
	void close();
	void redeem();
	void change();
	void list()const;
	void messeges()const;
	void help() const;
};

