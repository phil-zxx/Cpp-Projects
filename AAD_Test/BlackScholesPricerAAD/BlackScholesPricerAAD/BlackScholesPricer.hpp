#pragma once

#include <cmath>
#include <type_traits>
#include <vector>

#include <adept_source.h>
using adept::adouble;

#define OneOverSqrt2   0.707106781186547461715008466854
#define OneOverSqrt2Pi 0.398942280401432677939946059934

adept::Stack stack;


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

	template<class number>
	static std::vector<double> calcPriceGreeks(number S, number K, number r, number v, number T);

	static double CDF(const double x);
	static double PDF(const double x);

	static adouble CDF(const adouble x);
	static adouble PDF(const adouble x);

	double S, K, r, v, T;
};

// Inline Definitions

inline BlackScholesPricer::BlackScholesPricer(double SS, double KK, double rr, double vv, double TT)
	: S(SS), K(KK), r(rr), v(vv), T(TT) { }

inline double BlackScholesPricer::getPrice()
{
	return calcPrice<double>(S, K, r, v, T);
}

inline std::vector<double> BlackScholesPricer::getPriceGreeks_Analytical()
{
	return calcPriceGreeks<double>(S, K, r, v, T);
}

inline std::vector<double> BlackScholesPricer::getPriceGreeks_FD(const double h)
{
	const double basePrice = calcPrice<double>(S, K, r, v, T);

	std::vector<double> metrics({
		basePrice,																					// NPV		
		(calcPrice<double>(S + h, K, r, v, T) - calcPrice<double>(S - h, K, r, v, T)) / (2 * h),	// DeltaSpot
		(calcPrice<double>(S, K + h, r, v, T) - calcPrice<double>(S, K - h, r, v, T)) / (2 * h),	// DeltaStrike
		(calcPrice<double>(S, K, r + h, v, T) - calcPrice<double>(S, K, r - h, v, T)) / (2 * h),	// Rho
		(calcPrice<double>(S, K, r, v + h, T) - calcPrice<double>(S, K, r, v - h, T)) / (2 * h),	// Vega
		-(calcPrice<double>(S, K, r, v, T + h) - calcPrice<double>(S, K, r, v, T - h)) / (2 * h)	// Theta
		});

	return metrics;
}

inline std::vector<double> BlackScholesPricer::getPriceGreeks_AD()
{
	adouble S_AD = S, K_AD = K, r_AD = r, v_AD = v, T_AD = T;

	stack.new_recording();
	const adouble NPV = calcPrice<adouble>(S_AD, K_AD, r_AD, v_AD, T_AD);

	NPV.set_gradient(1.0);
	stack.compute_adjoint();

	std::vector<double> metrics({
		NPV.value(),			// NPV		
		S_AD.get_gradient(),	// DeltaSpot
		K_AD.get_gradient(),	// DeltaStrike
		r_AD.get_gradient(),	// Rho
		v_AD.get_gradient(),	// Vega
		-T_AD.get_gradient()	// Theta
		});

	return metrics;
}

inline double BlackScholesPricer::CDF(const double x) { return 0.5 * std::erfc(-(x * OneOverSqrt2)); }
inline double BlackScholesPricer::PDF(const double x) { return std::exp(-0.5 * x*x) * OneOverSqrt2Pi; }

inline adouble BlackScholesPricer::CDF(const adouble x) { return 0.5 * adept::erfc(-(x * OneOverSqrt2)); }
inline adouble BlackScholesPricer::PDF(const adouble x) { return adept::exp(-0.5 * x*x) * OneOverSqrt2Pi; }

template<class number>
inline number BlackScholesPricer::calcPrice(number S, number K, number r, number v, number T)
{
	const number sigSqrtT = v * sqrt(T);
	const number d1 = (log(S / K) + (r + 0.5*v*v)*T) / sigSqrtT;
	const number d2 = d1 - sigSqrtT;
	const number DF = exp(-r * T);
	const number PhiD1 = CDF(d1);
	const number PhiD2 = CDF(d2);

	return S * PhiD1 - K * PhiD2 * DF;
}

template<class number>
inline std::vector<double> BlackScholesPricer::calcPriceGreeks(number S, number K, number r, number v, number T)
{
	const number sigSqrtT = v * sqrt(T);
	const number d1 = (log(S / K) + (r + 0.5*v*v)*T) / sigSqrtT;
	const number d2 = d1 - sigSqrtT;
	const number DF = exp(-r * T);
	const number PhiD1 = CDF(d1);
	const number phiD1 = PDF(d1);
	const number PhiD2 = CDF(d2);

	std::vector<double> metrics({
		S * PhiD1 - K * PhiD2 * DF,						// NPV
		PhiD1,											// DeltaSpot
		-DF*PhiD2,										// DeltaStrike
		K*T*DF*PhiD2,									// Rho
		S * PDF(d1) * std::sqrt(T),						// Vega
		-0.5*S*phiD1*v / std::sqrt(T) - r * K*DF*PhiD2	// Theta
		});

	return metrics;
}