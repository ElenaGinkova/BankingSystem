#pragma once
#include "BankSystem.h"
#include "EmployeeRunner.h"
#include "ClientRunner.h"
#include "ThirdPartyEmployeeRunner.h"

class Excecuter
{
public:
	static void excecute(BankSystem& bankSystem);
	static void excecuteSystem(BankSystem& bankSystem);
};

