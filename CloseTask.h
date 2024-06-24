#pragma once
#include "Task.h"
#include "Account.h"
class CloseTask : public Task
{
public:
	CloseTask(UserInfo data, Account& acc, TaskType type);
	void viewInfo() const override;
	Account& getAccount()const;
	Task* clone() const override;
	void saveToFile(std::ofstream& ofs);
private:
	Account& acc;
};

