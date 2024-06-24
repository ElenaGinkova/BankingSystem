#pragma once
#include "Task.h"
#include "Account.h"
enum class TaskStatus
{
	NeedsApproval,
	Valid,
	Rejected
};

class ChangeTask : public Task
{
public:
	ChangeTask(const MyString& oldBank, const MyString& newBank, Account& acc, UserInfo data, TaskType type);
	void viewInfo() const override;
	Account& getAccount()const;
	const MyString& getOldBank();
	const MyString& getNewBank();
	void setStatus(TaskStatus);
	TaskStatus getStatus()const;
	void change();
	Task* clone() const override;
private:
	Account& acc;
	MyString oldBank;
	MyString newBank;
	TaskStatus status = TaskStatus::NeedsApproval;
};

