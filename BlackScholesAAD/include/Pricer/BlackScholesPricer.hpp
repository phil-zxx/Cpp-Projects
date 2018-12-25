#pragma once

#include <cmath>
#include <type_traits>
#include <vector>

#include <adept.h>
using adept::adouble;

#define OneOverSqrt2   0.707106781186547461715008466854
#define OneOverSqrt2Pi 0.398942280401432677939946059934


class BlackScholesPricer
{
public:
	BlackScholesPricer(double SS, double KK, double rr, double vv, double TT);

	double getPrice();

	std::vector<double> getPriceGreeks_Analytical();
	std::vector<double> getPriceGreeks_FD(const double h = 0.0001);
	std::vector<double> getPriceGreeks_AD();

private:
	template<class number>
	static number calcPrice(number S, number K, number r, number v, number T);

	static std::vector<double> calcPriceGreeks(double S, double K, double r, double v, double T);

	static double CDF(const double x);
	static double PDF(const double x);

	static adouble CDF(const adouble x);
	static adouble PDF(const adouble x);

	double S, K, r, v, T;
};


template<class number>
inline number BlackScholesPricer::calcPrice(number S, number K, number r, number v, number T)
{
    if constexpr (std::is_same_v<number, double>)
    {
        const number sigSqrtT = v * std::sqrt(T);
        const number d1       = (std::log(S / K) + (r + 0.5 * v * v) * T) / sigSqrtT;
        const number d2       = d1 - sigSqrtT;
        const number DF       = exp(-r * T);
        const number PhiD1    = CDF(d1);
        const number PhiD2    = CDF(d2);

        return S * PhiD1 - K * PhiD2 * DF;
    }
    else if constexpr (std::is_same_v<number, adouble>)
    {
        const number sigSqrtT = v * adept::sqrt(T);
        const number d1       = (adept::log(S / K) + (r + 0.5 * v * v) * T) / sigSqrtT;
        const number d2       = d1 - sigSqrtT;
        const number DF       = adept::exp(-r * T);
        const number PhiD1    = CDF(d1);
        const number PhiD2    = CDF(d2);

        return S * PhiD1 - K * PhiD2 * DF;
    }
    return 0;
}