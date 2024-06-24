#pragma once
#include "MyString.h"
#include "UserInfo.h"
#include <fstream>
enum class TaskType
{
	OPEN,
	CLOSE,
	CHANGE,
	DEFAULT
};

class Task
{
public:
	Task(UserInfo data, TaskType type);
	void setId(int id);
	void setName(const MyString& name);

	int getId() const;
	TaskType getType() const;
	UserInfo getUserInfo() const;
	const MyString& getUserId()const;

	void printTask() const;
	virtual void viewInfo() const = 0;
	virtual Task* clone() const = 0;
	virtual ~Task() = default;
protected:

	TaskType type;
	UserInfo data;
	int id = 0;
	MyString taskName;
	MyString message;

};
