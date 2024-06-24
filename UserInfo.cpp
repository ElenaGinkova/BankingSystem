#include "UserInfo.h"
#include <fstream>
 const size_t UserInfo::ID_LEN = 10;
 const size_t UserInfo::MAX_AGE = 130;

 static bool isDigit(char ch)
 {
	 return ch >= '0' && ch <= '9';
 }

 static bool onlyDigits(MyString id)
{
	int size = id.getSize();
	for (int i = 0; i < size; i++)
	{
		if (!isDigit(id[i]))
		{
			return false;
		}
	}
	return true;
}

UserInfo::UserInfo(const MyString& name, MyString id, size_t age, const MyString& password)
{
	if (id.getSize() != ID_LEN || !onlyDigits(id))
	{
		throw std::logic_error("Invalid id!");
	}
	if (age < 0 || age > MAX_AGE)
	{
		throw std::logic_error("Invalid age!");
	}
	this->name = name;
	this->id = id;
	this->age = age;
	this->password = password;
}

void UserInfo::printInfo() const
{
	std::cout << "Name: " << name << "\nEGN: " << id << "\nAge: " << age << std::endl;
}

const MyString& UserInfo::getName() const
{
	return name;
}

const MyString& UserInfo::getPassword() const
{
	return password;
}

const MyString& UserInfo::getUserId() const
{
	return id;
}

void UserInfo::saveToFile(std::ofstream& ofs)
{
	name.saveToFile(ofs);
	id.saveToFile(ofs);
	ofs.write((const char*)&age, sizeof(age));
	password.saveToFile(ofs);
}

void UserInfo::readFromFile(std::ifstream& ifs)
{
	name.readFromFile(ifs);
	id.readFromFile(ifs);
	ifs.read((char*)&age, sizeof(age));
	password.readFromFile(ifs);
}
