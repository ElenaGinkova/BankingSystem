#include "Cheque.h"

ChequeCode::ChequeCode(const char* data, double sum)
{
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
