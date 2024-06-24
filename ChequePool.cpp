#include "ChequePool.h"
#include <iostream>
#include <exception>
void ChequePool::resize()
{
	capacity *= 2;
	ChequeCode* newData = new ChequeCode[capacity];
	for (int i = 0; i < size; i++)
	{
		newData[i] = usedCodes[i];
	}
	delete[] usedCodes;
	usedCodes = newData;
}

void ChequePool::free()
{
	delete[] usedCodes;
}

bool ChequePool::chequeExists(const char* cheque) const
{
	for (int i = 0; i < size; i++)
	{
		if (!std::strcmp(usedCodes[i].getData(), cheque))
		{
			return true;
		}
	}
	return false;
}

const ChequeCode& ChequePool::allocate(const char* cheque, double sum)
{
	if (size == capacity)
	{
		resize();
	}
	usedCodes[size] = ChequeCode(cheque, sum);
	return usedCodes[size++];
}

ChequePool::ChequePool()
{
	usedCodes = new ChequeCode[capacity];
}

const ChequeCode& ChequePool::getAllocatedCode(const char* cheque, double sum)
{
	if (std::strlen(cheque) != 3)
	{
		throw std::logic_error("Invalid cheque");
	}
	if (chequeExists(cheque))
	{
		throw std::runtime_error("Cheque exists");
	}
	return allocate(cheque, sum);
}

ChequePool::~ChequePool()
{
	free();
}
