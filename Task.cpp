#include "Task.h"

Task::Task(UserInfo data, TaskType type) :type(type), data(data)
{
}

void Task::setIndx(int indx)
{
	this->indx = indx;
}

int Task::getIndx() const
{
	return indx;
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
	std::cout <<'['<< indx << "] " << taskName << " " << message;
}

