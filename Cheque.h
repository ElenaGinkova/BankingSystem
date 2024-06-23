#pragma once
struct ChequeCode
{
	ChequeCode() = default;
	ChequeCode(const char* data, double sum);
	const char* getData()const;
private:
	static const size_t CHEQUE_LEN = 3;
	char data[CHEQUE_LEN]{};
	double sum = 0.0;
};
