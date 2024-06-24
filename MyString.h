#pragma once
#include <iostream>
#include <fstream>
//from Angeld55 github

class MyString
{
public:
    MyString();
    MyString(const char* data);
    MyString(int num);

    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;

    MyString& operator=(const MyString& other);

    MyString& operator=(MyString&& other) noexcept;
    ~MyString();

    size_t getCapacity() const;
    size_t getSize() const;

    const char* c_str() const;

    MyString& operator+=(const MyString& other);

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
    friend std::istream& operator>>(std::istream& is, MyString& ref);
    friend MyString operator+(const MyString& lhs, const MyString& rhs);

    void saveToFile(std::ofstream& ofs);
    void readFromFile(std::ifstream& ifs);
private:
    char* numToStr(int num);
    char digitToChar(int digit);
    size_t numLen(int num);
    explicit MyString(size_t stringLength);
    void resize(unsigned newAllocatedDataSize);

    void free();
    void copyFrom(const MyString& other);

    void moveFrom(MyString&& other);

    char* _data;
    size_t _size;
    size_t _allocatedDataSize;
};



bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
