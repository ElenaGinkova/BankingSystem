#include "EmployeeRunner.h"
#include <iostream>
#include <exception>
const size_t EmployeeRunner::MAX_BUFF_SIZE = 1024;

static MyString taskTypeToStr(TaskType t)
{
	switch (t)
	{
	case TaskType::CHANGE: return "Change"; break;
	case TaskType::OPEN: return "Open"; break;
	case TaskType::CLOSE: return "Close"; break;
	}
}

void EmployeeRunner::getCustomMessage(MyString& message)
{
	std::cout << "Enter reason in format\"reason\": ";
	char ch = '\0';
	while (ch != '"')
	{
		std::cin >> ch;
	}
	char line[MAX_BUFF_SIZE]{};
	std::cin.getline(line, MAX_BUFF_SIZE, '"');
	message = line;
}

int EmployeeRunner::taskIndex()
{
	int taskId;
	std::cin >> taskId;
	if (taskId < 0)
	{
		throw std::logic_error("No such task");
	}
	return employee->getTaskIndx(taskId);
}

void EmployeeRunner::approve()
{
	int taskIndx = taskIndex();
	TaskType type = employee->getTask(taskIndx)->getType();
	switch (type)
	{
	case TaskType::OPEN: approveOpen(taskIndx); break;
	case TaskType::CHANGE: approveChange(taskIndx); break;
	case TaskType::CLOSE: approveClose(taskIndx); break;
	}
}

void EmployeeRunner::disapprove()
{
	int taskIndx = taskIndex();
	Task* task = (employee->getTask(taskIndx));
	const MyString& userId = task->getUserId();
	Client& client = *system.getClient(userId);
	MyString type = taskTypeToStr(task->getType());
	MyString mess = "Your " + type + " request was disapproved. Reason: ";
	sendCustomMessage(mess, client, taskIndx);
}

void EmployeeRunner::validateChange()
{
	int taskIndx = taskIndex();
	Task* task;
	try
	{
		task = employee->validate(taskIndx);
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what();
		return;
	}

	ChangeTask* changeTask = static_cast<ChangeTask*>(task);

	size_t accId = changeTask->getAccount().getAccId();
	MyString oldBankName = changeTask->getOldBank();
	Bank& oldBankRef = *system.findBank(oldBankName);
	size_t indx = oldBankRef.getAccIndx(accId);//if the account is invalid
											   //then the task will be rejected
	if (indx == -1)
	{
		changeTask->setStatus(TaskStatus::Rejected);
	}
	else
	{
		changeTask->setStatus(TaskStatus::Valid);
	}
}

void EmployeeRunner::help() const
{
	std::cout << "Commands:\n-tasks\n-view [task_id]\n-approve [task_id]\n-disapprove [task_id] [message]\n-validate [task_id]\n";
}

Client& EmployeeRunner::getClient(Task* task) const
{
	const MyString& userId = task->getUserId();
	return *system.getClient(userId);
}

void EmployeeRunner::sendCustomMessage(MyString mess, Client& client, size_t taskNum)
{
	MyString customMess;
	getCustomMessage(customMess);
	mess += customMess;
	client.recieveMessage(mess);
	employee->popTaskAtIndx(taskNum);
}

void EmployeeRunner::changeBanks(const MyString& oldB, const MyString& newB, size_t accId, Account& acc)
{
	Bank& oldBankRef = *system.findBank(oldB);
	Bank& newBankRef = *system.findBank(newB);

	oldBankRef.removeAccount(oldBankRef.getAccIndx(accId));
	newBankRef.addAccount(acc);
}

void EmployeeRunner::approveChange(size_t taskIndx)
{
	try {
		employee->approveChange(taskIndx);
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what();
		return;
	}

	ChangeTask* task = static_cast<ChangeTask*>(employee->getTask(taskIndx));
	TaskStatus status = task->getStatus();

	Client* client = system.getClient(task->getUserId());
	MyString mess;
	Account& acc = task->getAccount();
	int accId = acc.getAccId();

	if (status == TaskStatus::Valid)
	{
		mess = "You changed your savings account to " + task->getNewBank() + ".New account id is " + MyString(accId);
		changeBanks(task->getOldBank(), task->getNewBank(), accId, acc);
	}
	else if(status == TaskStatus::Rejected)
	{
		mess = employee->getName() + " rejected your change request to bank " + task->getNewBank() + " for account with id: " + MyString(accId);
	}

	employee->popTaskAtIndx(taskIndx);
	client->recieveMessage(mess);
}

void EmployeeRunner::approveOpen(size_t taskNum)
{
	Task& task = *employee->getTask(taskNum);
	const MyString& userId = task.getUserId();
	Client& client = *system.getClient(userId);
	Bank& bank = *system.findBank(employee->getBankName());

	Account& acc = employee->approveOpen(taskNum);
	bank.addAccount(std::move(acc));
	int accId = acc.getAccId();
	MyString mess = " You opened an account in " + bank.getName() + "! Your account id is " + MyString(accId);
	client.recieveMessage(mess);
	employee->popTaskAtIndx(taskNum);
}

void EmployeeRunner::approveClose(size_t taskNum)
{
	CloseTask* task = static_cast<CloseTask*>(employee->getTask(taskNum));

	Bank& bank = *system.findBank(employee->getBankName());
	size_t accIndx = bank.getAccIndx(task->getAccount().getAccId());
	Client& client = getClient(task);

	MyString mess = "Your Close request was approved.";
	if (accIndx == -1)
	{
		mess = "No account with this id exists!";
	}
	else
	{
		bank.removeAccount(accIndx);
	}
	client.recieveMessage(mess);
	employee->popTaskAtIndx(taskNum);
}

EmployeeRunner::EmployeeRunner(BankSystem& system):system(system)
{
}

void EmployeeRunner::runEmployee()
{
	MyString command;
	employee = static_cast<Employee*>(system.getLoggedIn());
	while(true)
	{
		std::cin >> command;
		try {
			if (command == "whoami")
			{
				employee->whoAmI();
			}
			else if (command == "exit")
			{
				system.logOut();
				break;
			}
			else if (command == "help")
			{
				help();
			}
			else if (command == "tasks")
			{
				employee->printTasks();
			}
			else if (command == "view")
			{
				int indx;
				std::cin >> indx;
				employee->view(indx);
			}
			else if (command == "approve")
			{
				approve();
			}
			else if (command == "disapprove")
			{
				disapprove();
			}
			else if (command == "validate")
			{
				validateChange();
			}
			else
			{
				std::cout << "No such command!";
			}
		}
		catch (std::exception& e)
		{
			std::cout << e.what();
		}
	}
}
