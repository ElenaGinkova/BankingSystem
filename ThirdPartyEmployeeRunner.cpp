#include "ThirdPartyEmployeeRunner.h"

ThirdPartyEmployeeRunner::ThirdPartyEmployeeRunner(BankSystem& system):system(system)
{
}

void ThirdPartyEmployeeRunner::runThirdPartyEmployee()
{
	MyString command;
	while (true)
	{
		std::cin >> command;
		try
		{
			if (command == "exit")
			{
				system.logOut();
				break;
			}
			else if (command == "help")
			{
				help();
			}
			else if (command == "whoami")
			{
				system.getLoggedIn()->whoAmI();
			}
			else if (command == "send_check")
			{
				sendCheque();
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

void ThirdPartyEmployeeRunner::help() const
{
	std::cout << "Commands:\n-send_check [sum] [verification_code] [egn]";
}

void ThirdPartyEmployeeRunner::sendCheque()
{
	double sum = 0.0;
	std::cin >> sum;
	MyString code, id;
	std::cin >> code >> id;

	ThirdPartyEmployee* employee = static_cast<ThirdPartyEmployee*>(system.getLoggedIn());
	const ChequeCode& cheque = employee->make_check(sum, code.c_str());
	Client& client = *system.getClient(id);
	client.recieveCheque(cheque);

	MyString mess("You have a check assigned to you by ");
	mess += employee->getName();
	client.recieveMessage(mess);
}