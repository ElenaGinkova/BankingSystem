#pragma once
#include "MyString.h"
#include "UserInfo.h"
enum class TaskType
{
	OPEN,
	CLOSE,
	CHANGE,
	DEFAULT
	//VALIDATE
};

class Task
{
public:
	Task(UserInfo data, TaskType type);
	void setIndx(int indx);

	int getIndx() const;
	TaskType getType() const;
	UserInfo getUserInfo() const;
	const MyString& getUserId()const;

	void printTask() const;
	virtual void viewInfo() const = 0;
	virtual Task* clone() const = 0;
	virtual ~Task() = default;
	//void setMessege(const MyString&);
protected:
	int indx;//setByBankingSystem
	MyString taskName;
	MyString message;
	TaskType type;
	UserInfo data;
};