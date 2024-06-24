#include "CloseTask.h"

CloseTask::CloseTask(UserInfo data, Account& acc, TaskType type) : Task(data, type), acc(acc)
{
	this->taskName = "Close - ";
	message += data.getName();
	message += " wants to close an account";
}

void CloseTask::viewInfo() const
{
	std::cout << taskName << " request from:\n";
	data.printInfo();
	acc.printInfo();
}
Account& CloseTask::getAccount() const
{
	return acc;
}
Task* CloseTask::clone() const
{
	return new CloseTask(*this);
}

void CloseTask::saveToFile(std::ofstream& ofs)
{
	size_t accID = acc.getAccId();
	ofs.write((const char*)(&accID), sizeof(size_t));
}
