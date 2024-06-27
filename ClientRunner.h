#pragma once
#include "Runner.h"
#include "BankSystem.h"
class ClientRunner : public Runner
{
public:
	ClientRunner(BankSystem& system);

	void run() override;
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

