#pragma once
#include <iostream>
#include <fstream>
#include "Vector.hpp"
#include "Cheque.h"
#include "UserInfo.h"

class User
{
public:
	User() = default;
	User(const MyString& name, const MyString& id, size_t age, MyString password);
	void whoAmI() const;
	const MyString& getName()const;
	bool isValidUser(MyString name, MyString password)const;
	virtual ~User() = default;
protected:
	UserInfo data;
};
