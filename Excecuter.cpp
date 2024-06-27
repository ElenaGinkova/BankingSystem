#include "Excecuter.h"

void Excecuter::excecute(BankSystem& bankSystem)
{
    MyString command;
    while (true)
    {
        std::cin >> command;
        if (command == "login")
        {
            bankSystem.logIn();
            excecuteSystem(bankSystem);
        }
        else if (command == "signup")
        {
            bankSystem.signUp();
        }
        else if (command == "create_bank")
        {
            bankSystem.createBank();
        }
        else if (command == "exit")
        {
            bankSystem.saveToFile();
            break;
        }
        else
        {
            std::cout << "No such command!";
        }
    }
}

void Excecuter::excecuteSystem(BankSystem& bankSystem)
{
    static EmployeeRunner employeeRunner(bankSystem);
    static ClientRunner clientRunner(bankSystem);
    static ThirdPartyEmployeeRunner thirdPartyEmployeeRunner(bankSystem);

    switch (bankSystem.getUserType())
    {
    case UserType::EmployeeType:  employeeRunner.run(); break;
    case UserType::ClientType: clientRunner.run(); break;
    case UserType::ThridPartyEmployeeType: thirdPartyEmployeeRunner.run(); break;
    }
}
