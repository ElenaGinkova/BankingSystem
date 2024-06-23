#include "UserInfo.h"

 const size_t UserInfo::ID_LEN = 10;
 const size_t UserInfo::MAX_AGE = 130;

size_t digitsCount(size_t num)
{
	size_t count = 0;
	while (num)
	{
		count++;
		num /= 10;
	}
	return count;
}

UserInfo::UserInfo(const MyString& name, MyString id, size_t age, const MyString& password)
{
	if (id.getSize() != ID_LEN)
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
	std::cout << "Name: " << name << "\nEGN: " << id << "\nAge: " << age;
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
