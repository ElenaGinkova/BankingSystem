#include "User.h"

User::User(MyString name, size_t id, size_t age, MyString password) : id(id), age(age)
{
	this->name = name;
	this->password = password;
}

void User::whoAmI() const
{
	std::cout << "You are " << name;
}



bool User::isValidUser(MyString name, MyString password) const
{
	if (this->name == name && this->password == password)
	{
		return true;
	}
	return false;
}
