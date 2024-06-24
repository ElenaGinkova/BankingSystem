#include "Cheque.h"
#include <exception>
#include <iostream>
#include <fstream>

ChequeCode::ChequeCode(const char* data, double sum)
{
	if (!validate(data))
	{
		throw std::runtime_error("Invalid check code");
	}
	for (int i = 0; i < CHEQUE_LEN; i++)
	{
		this->data[i] = data[i];
	}
	this->sum = sum;
}

const char* ChequeCode::getData() const
{
	return data;
}

double ChequeCode::getSum() const
{
	return sum;
}

void ChequeCode::saveToFile(std::ofstream& ofs)
{
	ofs.write((const char*)(data), sizeof(char) * CHEQUE_LEN);
	ofs.write((const char*)(&sum), sizeof(sum));
}

void ChequeCode::readFromFile(std::ifstream& ifs)
{
	ifs.read((char*)(data), sizeof(char) * CHEQUE_LEN);
	ifs.read((char*)(&sum), sizeof(sum));
}

bool ChequeCode::isValidChar(char ch) const
{
	return ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

bool ChequeCode::validate(const char* data) const
{
	for (int i = 0; i < CHEQUE_LEN - 1; i++)
	{
		if (!isValidChar(data[i]))
		{
			return false;
		}
	}
	return true;
}
