#pragma once
#include "MyString.h"
class UserInfo
{
public:
	UserInfo() = default;
	UserInfo(const MyString& name, MyString id, size_t age, const MyString& password);
	void printInfo() const;
	const MyString& getName()const;
	const MyString& getPassword()const;
	const MyString& getUserId()const;

	void saveToFile(std::ofstream& ofs);
	void readFromFile(std::ifstream& ifs);
private:
	static const size_t ID_LEN;
	static const size_t MAX_AGE;

	MyString name;
	MyString id;
	size_t age = 0;
	MyString password;
};

