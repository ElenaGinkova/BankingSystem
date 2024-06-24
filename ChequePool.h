#pragma once
#include "Cheque.h"
class ChequePool
{
private:
	ChequeCode* usedCodes = nullptr;
	size_t size = 0;
	size_t capacity = 4;

	void resize();
	void free();

	bool chequeExists(const char*)const;
	const ChequeCode& allocate(const char*, double sum);
public:
	ChequePool();

	const ChequeCode& getAllocatedCode(const char*, double sum);

	ChequePool(const ChequePool&) = delete;
	ChequePool& operator=(const ChequePool&) = delete;

	~ChequePool();
};

