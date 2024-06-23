#pragma once
#include "Task.h"
#include "UserInfo.h"

class OpenTask : public Task
{
public:
	OpenTask(UserInfo data, TaskType type);
	Task* clone() const override;
	void viewInfo() const override;
	
private:
};
