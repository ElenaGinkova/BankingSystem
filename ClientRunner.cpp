#include "ClientRunner.h"

ClientRunner::ClientRunner(BankSystem& system):system(system)
{
}

void ClientRunner::runClient()
{
	MyString command;
	Client* client = static_cast<Client*>(system.getLoggedIn());
	while (true)
	{
		std::cin >> command;
		try {
			if (command == "help")
			{
				help();
			}
			else if (command == "whoami")
			{
				client->whoAmI();
			}
			else if (command == "check_avl")
			{
				checkAvailability();
			}
			else if (command == "open")//task is dynamic obj but 
									   //polymorphic container in employee takse care
			{
				open(client);
			}
			else if (command == "close")
			{
				close(client);
			}
			else if (command == "redeem")
			{
				//
			}
			else if (command == "change")
			{
				change(client);
			}
			else if (command == "list")
			{
				list(client);
			}
			else if (command == "messages")
			{
				messeges(client);
			}
			else if (command == "exit")
			{
				system.logOut();
				break;
			}
			else
			{
				std::cout << "Invalid command";
			}

		}
		catch (std::exception& e)
		{
			std::cout << e.what();
		}
		
	}
}

void ClientRunner::fromConsole(MyString& bankName, int& accId)
{
	std::cout << "Bank name: ";
	std::cin >> bankName;
	std::cout << "Account number: ";
	std::cin >> accId;
}

void ClientRunner::checkAvailability()
{
	MyString bankName;
	int accId = -1;
	fromConsole(bankName, accId);
	Bank* bank = system.findBank(bankName);
	bank->checkAvailability(accId);
}

void ClientRunner::open(Client* client)
{
	MyString bankName;
	std::cin >> bankName;
	Task* task = client->open();
	Bank* bank = system.findBank(bankName);
	bank->giveTask(task);
}

void ClientRunner::close(Client* client)
{
	MyString bankName;
	int accId = -1;
	fromConsole(bankName, accId);
	Bank* bank = system.findBank(bankName);
	Account* acc = bank->getAccount(accId);
	Task* task = client->close(acc);
	bank->giveTask(task);
}

void ClientRunner::change(Client* client)
{
	MyString newBankName;
	std::cout << "NewBankName: ";
	std::cin >> newBankName;
	MyString currBankName;
	int accId = -1;
	fromConsole(currBankName, accId);
	Bank* currBank = system.findBank(currBankName);
	Account* acc = currBank->getAccount(accId);
	Task* task = client->change(newBankName, currBankName, acc);
	Bank* newBank = system.findBank(newBankName);
	newBank->giveTask(task);
}

void ClientRunner::list(Client* client) const
{
	MyString bankName;
	std::cin >> bankName;
	Bank* bank = system.findBank(bankName);
	bank->list(client->getUserId());
}

void ClientRunner::messeges(Client* client) const
{
	client->printMesseges();
}

void ClientRunner::help() const
{
	std::cout << "Commands:\n-check_avl [bank_name] [account_number]\n-open [bank_name]\n-close [bank_name] [account_number] \n-redeem [bank_name] [account_number] [verification_code] \n-change [new_bank_name] [current_bank_name] [account_number]\n-list [bank_name]\n-messeges";
}