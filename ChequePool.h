#pragma once
#include "Cheque.h"
class ChequePool
{
private:
	
	ChequeCode* usedCodes = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void resize();
	void free();
public:
	ChequePool() = default;

	int validateCode(const char*);
	const ChequeCode* getAllocatedCode(const char*);

	ChequePool(const ChequePool&) = delete;
	ChequePool& operator=(const ChequePool&) = delete;

	~ChequePool();
};

