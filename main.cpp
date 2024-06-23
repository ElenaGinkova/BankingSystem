#include <iostream>
#include "EmployeeRunner.h"
#include "ClientRunner.h"
#include "ThirdPartyEmployeeRunner.h"

void runBankSystem(BankSystem& bankSystem)
{
    static EmployeeRunner employeeRunner(bankSystem);
    static ClientRunner clientRunner(bankSystem);
    static ThirdPartyEmployeeRunner thirdPartyEmployeeRunner(bankSystem);

    switch (bankSystem.getUserType())
    {
    case UserType::EmployeeType:  employeeRunner.runEmployee(); break;
    case UserType::ClientType: clientRunner.runClient(); break;
    case UserType::ThridPartyEmployeeType: thirdPartyEmployeeRunner; break;
    }

}

void run(BankSystem& bankSystem)
{
    MyString command;
    while (command != "exit")
    {
        std::cin >> command;
        if (command == "login")
        {
            bankSystem.logIn();
            runBankSystem(bankSystem);
        }
        else if (command == "signup")
        {
            bankSystem.signUp();
        }
        else if (command == "create_bank")
        {
            bankSystem.createBank();
        }
        else
        {
            std::cout << "No such command!";
        }
    }
}

int main()
{
   BankSystem bankSystem;
   run(bankSystem);
}
