#include <iostream>
#include <chrono>

using namespace std;

class Currency
{
public:
	Currency(const char ccyCode[4])
	{
		_ccyCode[0] = ccyCode[0];
		_ccyCode[1] = ccyCode[1];
		_ccyCode[2] = ccyCode[2];
		_ccyCode[3] = ccyCode[3];
	}

private:
	char _ccyCode[4];
};

class CurrencyInt
{
public:
	CurrencyInt(const int ccyHash)
		: _ccyHash(ccyHash) { }
	
private:
	int _ccyHash;
};

int main_old()
{
	const size_t n = 100'000'000;
	const double nano = 1'000'000'000.;
	const char ccyCode[4] = "EUR";
	const int ccyHash = 5147843;
	size_t i;

	auto startTime1 = std::chrono::high_resolution_clock::now();
	for (i = 0; i < n; ++i)
		Currency ccy1(ccyCode);
	auto endTime1 = std::chrono::high_resolution_clock::now();
	cout << (endTime1 - startTime1).count() / nano << "\n";

	auto startTime2 = std::chrono::high_resolution_clock::now();
	for (i = 0; i < n; ++i)
		CurrencyInt ccy2(ccyHash);
	auto endTime2 = std::chrono::high_resolution_clock::now();
	cout << (endTime2 - startTime2).count() / nano << "\n";

	return 0;
}