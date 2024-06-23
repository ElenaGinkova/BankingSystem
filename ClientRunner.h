#pragma once
#include "BankSystem.h"
class ClientRunner
{
public:
	ClientRunner(BankSystem& system);

	void runClient();
private:
	BankSystem& system;

	void fromConsole(MyString&, int&);
	void checkAvailability();//public or private?
	void open(Client* client);
	void close(Client* client);

	void change(Client* client);
	void list(Client* client)const;
	void messeges(Client* client)const;
	void help() const;
};

