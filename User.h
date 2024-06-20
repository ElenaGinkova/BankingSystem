#pragma once
#include <iostream>
#include "MyString.h"
#include "Vector.hpp"
#include "Cheque.h"


//abstract?
class User
{
protected:

	MyString name;
	MyString surname;
	MyString password;
	size_t id;
	size_t age;

public:
	User(MyString name, size_t id, size_t age, MyString password);

	//addcheque
	//osrebricheck
	void whoAmI() const;

	bool isValidUser(MyString name, MyString password)const;

	virtual ~User() = default;
};
