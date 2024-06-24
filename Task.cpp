#include "Task.h"

Task::Task(UserInfo data, TaskType type) :type(type), data(data)
{
}
void Task::setId(int id)
{
	this->id = id;
}


void Task::setName(const MyString& name)
{
	taskName = name;
}


int Task::getId() const
{
	return id;
}

TaskType Task::getType() const
{
	return type;
}

UserInfo Task::getUserInfo() const
{
	return data;
}

const MyString& Task::getUserId() const
{
	return data.getUserId();
}



void Task::printTask() const
{
	std::cout << '[' << id << "] - " << taskName << " " << message;
}

