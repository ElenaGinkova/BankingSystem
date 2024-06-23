#include "ChangeTask.h"

ChangeTask::ChangeTask(const MyString& newBank, const MyString& oldBank, Account* acc, UserInfo data, TaskType type) : Task(data, type), oldBank(oldBank), newBank(newBank), acc(acc)
{
	this->taskName = "Change - ";
	message += data.getName();
	message += " wants to transfer account from ";
	message += oldBank;
}

void ChangeTask::viewInfo() const
{
	std::cout << taskName << " request from:\n";
	data.printInfo();
	acc->printInfo();
}

Account* ChangeTask::getAccount() const
{
	return acc;
}

const MyString& ChangeTask::getOldBank()
{
	return oldBank;
}

const MyString& ChangeTask::getNewBank()
{
	return newBank;
}

void ChangeTask::setStatus(TaskStatus status)
{
	this->status = status;
}


TaskStatus ChangeTask::getStatus() const
{
	return status;
}

void ChangeTask::change()
{
	acc->changeBank(newBank);
}

Task* ChangeTask::clone() const
{
	return new ChangeTask(*this);
}