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
    tasks.add(task);
}

void Employee::printTasks() const
{
    for (int i = 0; i < getTasksCount(); i++)
    {
        tasks[i].get()->printTask();
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

void Employee::view(int taskIndx) const
{
    if (taskIndx < 0 || taskIndx >= tasks.getSize())
    {
        throw std::logic_error("No such task");
    }
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


