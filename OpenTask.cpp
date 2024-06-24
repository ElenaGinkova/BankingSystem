#include "OpenTask.h"

OpenTask::OpenTask(UserInfo data, TaskType type) : Task(data, type)
{
	this->taskName = "Open - ";
	message += data.getName();
	message += " wants to create an account";
}

Task* OpenTask::clone() const
{
	return new OpenTask(*this);
}

void OpenTask::viewInfo() const
{
	std::cout << taskName << " request from:\n";
	data.printInfo();
}

void OpenTask::saveToFile(std::ofstream& ofs)
{
	ofs.write((const char*)(&type), sizeof(TaskType));
	data.saveToFile(ofs);
	ofs.write((const char*)(&id), sizeof(id));
	taskName.saveToFile(ofs);
	message.saveToFile(ofs);
}
