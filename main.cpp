#include <iostream>
#include "Excecuter.h"

int main()
{
   BankSystem bankSystem;
   bankSystem.readFromFile();
   Excecuter::excecute(bankSystem);
}
