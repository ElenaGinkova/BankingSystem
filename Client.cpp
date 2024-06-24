#include "Client.h"

Client::Client(const MyString& name, const MyString& id, size_t age, MyString password) : User(name, id, age, password)
{

}

Task* Client::open()
{
	OpenTask* task = new OpenTask(data, TaskType::OPEN);
	return task;
}

Task* Client::close(Account& acc)
{
	CloseTask* task = new CloseTask(data, acc, TaskType::CLOSE);
	return task;
}
void Client::printMesseges() const
{
	for (int i = 0; i < messeges.getSize(); i++)
	{
		std::cout << '[' << i + 1 << "] - " << messeges[i] << std::endl;
	}
}
const ChequeCode& Client::getCheque(const MyString& verificationCode) const
{
	return cheques[findChequeInd(verificationCode)];
}
void Client::redeemCheque(const MyString& verificationCode)
{
	cheques.popAt(findChequeInd(verificationCode));
}
void Client::recieveCheque(const ChequeCode& code)
{
	cheques.pushBack(code);
}
const MyString& Client::getUserId() const
{
	return data.getUserId();
}
void Client::recieveMessage(const MyString& message)
{
	messeges.pushBack(message);
}
void Client::checkAvailabilty(Account* acc) const
{
	acc->checkAvailability();
}
void Client::saveToFile(std::ofstream& ofs)
{
	data.saveToFile(ofs);
	size_t count = messeges.getSize();
	ofs.write((const char*)(&count), sizeof(count));
	for (int i = 0; i < messeges.getSize(); i++)
	{
		messeges[i].saveToFile(ofs);
	}
	count = cheques.getSize();
	ofs.write((const char*)(&count), sizeof(count));
	for (int i = 0; i < cheques.getSize(); i++) 
	{
		cheques[i].saveToFile(ofs);
	}
}
void Client::readFromFile(std::ifstream& ifs)
{
	data.readFromFile(ifs);
	size_t count = 0;
	ifs.read((char*)(&count), sizeof(count));
	for (int i = 0; i < count; i++)
	{
		MyString messege;
		messege.readFromFile(ifs);
		messeges.pushBack(messege);
	}
	ifs.read((char*)(&count), sizeof(count));
	for (int i = 0; i < count; i++)
	{
		ChequeCode cheque;
		cheque.readFromFile(ifs);
		cheques.pushBack(cheque);
	}
}
int Client::findChequeInd(const MyString& verificationCode) const
{
	for (int i = 0; i < cheques.getSize(); i++)
	{
		if (cheques[i].getData() == verificationCode)
		{
			return i;
		}
	}
	throw std::runtime_error("No such cheque found");
}
Task* Client::change(const MyString& newBank, const MyString& oldBank, Account& acc)
{
	ChangeTask* task = new ChangeTask(newBank, oldBank, acc, data, TaskType::CHANGE);
	return task;
}
