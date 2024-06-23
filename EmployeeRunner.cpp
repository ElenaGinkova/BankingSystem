#include "EmployeeRunner.h"
#include <iostream>
#include <exception>
const size_t EmployeeRunner::MAX_BUFF_SIZE = 1024;

size_t numLen(int num)
{
	size_t res = 1;
	while (num)
	{
		res++;
		num /= 10;
	}
	return res;
}

char digitToChar(int digit)
{
	return digit + '0';
}

MyString numToStr(int num)
{
	int len = numLen(num);
	char* res = new char[len + 1] {};
	for (int i = len - 1; i >= 0; i--)
	{
		res[0] = digitToChar(num % 10);
		num /= 10;
	}
	res[len] = '\0';
	MyString string(res);
	delete[] res;
	return string;
}

MyString taskTypeToStr(TaskType t)
{
	switch (t)
	{
	case TaskType::CHANGE: return "Change"; break;
	case TaskType::OPEN: return "Open"; break;
	case TaskType::CLOSE: return "Close"; break;
	}
}

/////////

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

void EmployeeRunner::approve(Employee& employee)
{
	int taskNum;
	std::cin >> taskNum;
	if (taskNum < 0 || taskNum >= employee.getTasksCount())
	{
		throw std::logic_error("No such task");
	}
	TaskType type = employee.getTask(taskNum)->getType();
	switch (type)
	{
	case TaskType::OPEN: approveOpen(employee, taskNum); break;
	case TaskType::CHANGE: approveChange(employee, taskNum); break;
	case TaskType::CLOSE: approveClose(employee, taskNum); break;
	}
}

void EmployeeRunner::disapprove(Employee& employee)
{
	size_t taskNum;
	std::cin >> taskNum;
	if (taskNum < 0 || taskNum >= employee.getTasksCount())
	{
		throw std::logic_error("No such task");
	}
	Task* task = (employee.getTask(taskNum));
	const MyString& userId = task->getUserId();
	Client& client = *system.getClient(userId);
	MyString type = taskTypeToStr(task->getType());
	MyString mess = "Your " + type + " request was disapproved. Reason: ";
	sendCustomMessage(mess, client, employee, taskNum);
}

void EmployeeRunner::validateChange(Employee& employee)
{
	size_t taskNum;
	std::cin >> taskNum;
	if (taskNum < 0 || taskNum >= employee.getTasksCount())
	{
		throw std::logic_error("No such task");
	}
	Task* task;
	try
	{
		task = employee.validate(taskNum);
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what();
		return;
	}

	ChangeTask* changeTask = static_cast<ChangeTask*>(task);

	size_t accId = changeTask->getAccount()->getAccId();
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

void EmployeeRunner::sendCustomMessage(MyString mess, Client& client, Employee& employee, size_t taskNum)
{
	MyString customMess;
	getCustomMessage(customMess);
	mess += customMess;
	client.recieveMessage(mess);
	employee.popTaskAtIndx(taskNum);
}

void EmployeeRunner::changeBanks(const MyString& oldB, const MyString& newB, size_t accId, Account* acc)
{
	Bank& oldBankRef = *system.findBank(oldB);
	Bank& newBankRef = *system.findBank(newB);

	oldBankRef.removeAccount(oldBankRef.getAccIndx(accId));
	newBankRef.addAccount(*acc);
}

void EmployeeRunner::approveChange(Employee& employee, size_t taskIndx)
{
	try {
		employee.approveChange(taskIndx);
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what();
		return;
	}

	ChangeTask* task = static_cast<ChangeTask*>(employee.getTask(taskIndx));
	TaskStatus status = task->getStatus();

	Client* client = system.getClient(task->getUserId());
	MyString mess;
	Account* acc = task->getAccount();
	size_t accId = acc->getAccId();

	if (status == TaskStatus::Valid)
	{
		mess = "You changed your savings account to " + task->getNewBank() + ".New account id is " + numToStr(accId);
		changeBanks(task->getOldBank(), task->getNewBank(), accId, acc);
	}
	else if(status == TaskStatus::Rejected)
	{
		mess = employee.getName() + " rejected your change request to bank " + task->getNewBank() + " for account with id: " + numToStr(accId);
	}

	employee.popTaskAtIndx(taskIndx);
	client->recieveMessage(mess);
}

void EmployeeRunner::approveOpen(Employee& employee, size_t taskNum)
{
	Task& task = *employee.getTask(taskNum);
	const MyString& userId = task.getUserId();
	Client& client = *system.getClient(userId);
	Bank& bank = *system.findBank(employee.getBankName());

	Account& acc = employee.approveOpen(taskNum);
	bank.addAccount(std::move(acc));
	MyString mess = " You opened an account in" + bank.getName() + "! Your account id is" + numToStr(acc.getAccId());
	client.recieveMessage(mess);
	employee.popTaskAtIndx(taskNum);
}

void EmployeeRunner::approveClose(Employee& employee, size_t taskNum)
{
	CloseTask* task = static_cast<CloseTask*>(employee.getTask(taskNum));

	Bank& bank = *system.findBank(employee.getBankName());
	size_t accIndx = bank.getAccIndx(task->getAccount()->getAccId());
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
	employee.popTaskAtIndx(taskNum);
}

EmployeeRunner::EmployeeRunner(BankSystem& system):system(system)
{
}

void EmployeeRunner::runEmployee()
{
	MyString command;
	Employee* employee = static_cast<Employee*>(system.getLoggedIn());
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
				approve(*employee);
			}
			else if (command == "disapprove")
			{
				disapprove(*employee);
			}
			else if (command == "validate")
			{
				validateChange(*employee);
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