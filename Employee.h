#pragma once
#include "User.h"
#include "Vector.hpp"
#include "Task.h"
#include "Client.h"
#include "PolymorphicCointainer.hpp"

class Employee : public User
{
public:
	Employee() = default;
	Employee(const MyString& name, const MyString& id, size_t age, MyString password, const MyString& bankName);
	
	void addTask(Task* task);
	void printTasks() const;
	void view(int taskIndx) const;

	int getTasksCount() const;
	Task* getTask(int taskIndx);
	const MyString& getBankName()const;

	Task* validate(size_t taskIndx);
	void popTaskAtIndx(size_t indx);

	Account& approveOpen(size_t taskIndx);
	void approveChange(size_t taskIndx);
	size_t getTaskIndx(int taskID)const;
	
	void saveToFile(std::ofstream& ofs);
	void readFromFile(std::ifstream& ifs);
private:
	

	int nextTaskId = 0;//personal for each employee

	polymorphic_container<Task> tasks;
	MyString bankName;
};
