#include <iostream>
#include <chrono>

#include "BlackScholesPricer.hpp"

using namespace std;


class Clock
{
public:
	static void startTimer()
	{ 
		lastCheck = chrono::high_resolution_clock::now().time_since_epoch().count(); 
	}

	static void stopTimer()  
	{ 
		std::cout << "\nTime passed: " << (chrono::high_resolution_clock::now().time_since_epoch().count() - lastCheck)/1000000000. << " seconds" << std::endl;
	}

private:
	static long long lastCheck;
};

long long Clock::lastCheck;


int main()
{
	BlackScholesPricer pricer = BlackScholesPricer(100., 90., 0.0172, 0.15, 2.);
	std::vector<double> metrics;
	size_t trials = 500000;

	Clock::startTimer(); 
	for (size_t i = 0; i < trials; ++i) metrics = pricer.getPriceGreeks_Analytical();
	Clock::stopTimer();
	for (const double& m : metrics) printf("%15.10f\n", m);

	Clock::startTimer(); 
	for (size_t i = 0; i < trials; ++i) metrics = pricer.getPriceGreeks_FD();
	Clock::stopTimer();
	for (const double& m : metrics) printf("%15.10f\n", m);

	Clock::startTimer(); 
	for (size_t i = 0; i < trials; ++i) metrics = pricer.getPriceGreeks_AD();
	Clock::stopTimer();
	for (const double& m : metrics) printf("%15.10f\n", m);
	
	return 0;
}