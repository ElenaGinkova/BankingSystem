#include "Employee.h"
int Employee::getTasksCount() const
{
    return tasks.getSize();
}

Employee::Employee(const MyString& name, const MyString& id, size_t age, MyString password, const MyString& bankName) : User(name, id, age, password), bankName(bankName)
{
}

void Employee::addTask(Task* task)
{
    task->setId(nextTaskId++);
    tasks.add(task);
}

void Employee::printTasks() const
{
    if (getTasksCount() == 0)
    {
        std::cout << "No tasks" << std::endl;
        return;
    }
    for (int i = 0; i < getTasksCount(); i++)
    {
        tasks[i].get()->printTask();
        std::cout << std::endl;
    }
}

Task* Employee::getTask(int taskIndx)
{
    if (taskIndx < 0 || taskIndx > tasks.getSize())
    {
        throw std::logic_error("Out of bounds");
    }
    return tasks[taskIndx].get();
}

const MyString& Employee::getBankName() const
{
    return bankName;
}

void Employee::view(int taskId) const
{
    int taskIndx = getTaskIndx(taskId);
    
    tasks[taskIndx].get()->viewInfo();
}

Task* Employee::validate(size_t taskIndx)
{
    if (tasks[taskIndx].get()->getType() != TaskType::CHANGE)
    {
        throw std::logic_error("Cannot validate this task!");
    }
    else if (taskIndx < 0 || taskIndx > tasks.getSize())
    {
        throw std::logic_error("Index out of bounds");
    }
    tasks[taskIndx].get()->setName("Change (validated)");
    return tasks[taskIndx].get();
}

void Employee::popTaskAtIndx(size_t indx)
{
    tasks.remove(indx);
}

Account& Employee::approveOpen(size_t taskIndx)
{
    OpenTask* task = static_cast<OpenTask*>(tasks[taskIndx].get());
    Account* acc = new Account(bankName, task->getUserId());
    return *acc;
}

void Employee::approveChange(size_t taskIndx)
{
    ChangeTask* task = static_cast<ChangeTask*>(tasks[taskIndx].get());
    TaskStatus status = task->getStatus();
    if (status == TaskStatus::Valid)
    {
        task->change();
    }
    else if (status == TaskStatus::NeedsApproval)
    {
        MyString message("Cannot proceed - please make sure");
        message += task->getUserInfo().getName();
        message += " is real user by asking the bank!";
        throw std::logic_error(message.c_str());
    }
}

size_t Employee::getTaskIndx(int taskID) const
{
    for (int i = 0; i < tasks.getSize(); i++)
    {
        if (tasks[i].get()->getId() == taskID)
        {
            return i;
        }
    }
    throw std::runtime_error("No such task");
}

void Employee::saveToFile(std::ofstream& ofs)
{
    data.saveToFile(ofs);
    bankName.saveToFile(ofs);
}

void Employee::readFromFile(std::ifstream& ifs)
{
    data.readFromFile(ifs);
    bankName.readFromFile(ifs);
}


