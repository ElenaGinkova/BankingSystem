#pragma once
#include <fstream>
struct ChequeCode
{
	ChequeCode() = default;
	ChequeCode(const char* data, double sum);
	const char* getData()const;
	double getSum()const;

	void saveToFile(std::ofstream& ofs);
	void readFromFile(std::ifstream& ifs);
private:
	bool isValidChar(char ch)const;
	bool validate(const char*)const;
	static const size_t CHEQUE_LEN = 4;

	char data[CHEQUE_LEN]{};
	double sum = 0.0;
};
