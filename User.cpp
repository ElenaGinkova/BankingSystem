#include "User.h"

User::User(const MyString& name, const MyString& id, size_t age, MyString password) : data(name, id, age, password)
{
}

void User::whoAmI() const
{
	std::cout << "You are " << data.getName();
}

const MyString& User::getName() const
{
	return data.getName();
}


bool User::isValidUser(MyString name, MyString password) const
{
	if (data.getName() == name && data.getPassword() == password)
	{
		return true;
	}
	return false;
}
