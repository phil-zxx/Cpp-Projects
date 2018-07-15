#include "BlackScholesPricer.hpp"
using adept::adouble;


BlackScholesPricer::BlackScholesPricer(double SS, double KK, double rr, double vv, double TT)
	: S(SS), K(KK), r(rr), v(vv), T(TT) { }

double BlackScholesPricer::getPrice()
{
	return calcPrice<double>(S, K, r, v, T);
}

std::vector<double> BlackScholesPricer::getPriceGreeks_Analytical()
{
	return calcPriceGreeks<double>(S, K, r, v, T);
}

std::vector<double> BlackScholesPricer::getPriceGreeks_FD(const double h = 0.001)
{
	const double basePrice = calcPrice<double>(S, K, r, v, T);

	std::vector<double> metrics({
		basePrice,												// NPV		
		(calcPrice<double>(S + h, K, r, v, T) - basePrice) / h,	// DeltaSpot
		(calcPrice<double>(S, K + h, r, v, T) - basePrice) / h,	// DeltaStrike
		(calcPrice<double>(S, K, r + h, v, T) - basePrice) / h,	// Rho
		(calcPrice<double>(S, K, r, v + h, T) - basePrice) / h,	// Vega
		(calcPrice<double>(S, K, r, v, T + h) - basePrice) / h	// Theta
		});

	return metrics;
}

std::vector<double> BlackScholesPricer::getPriceGreeks_AD()
{
	adept::Stack stack;
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
		T_AD.get_gradient()		// Theta
		});

	return metrics;
}

	template<class number>
	static number BlackScholesPricer::calcPrice(number S, number K, number r, number v, number T)
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
	static std::vector<double> BlackScholesPricer::calcPriceGreeks(number S, number K, number r, number v, number T)
	{
		const number sigSqrtT = v * sqrt(T);
		const number d1 = (log(S / K) + (r + 0.5*v*v)*T) / sigSqrtT;
		const number d2 = d1 - sigSqrtT;
		const number DF = exp(-r * T);
		const number PhiD1 = CDF(d1);
		const number PhiD2 = CDF(d2);

		std::vector<double> metrics({
			S * PhiD1 - K * PhiD2 * DF,					// NPV
			PhiD1,										// DeltaSpot
			0,											// DeltaStrike
			K*T*DF*PhiD2,								// Rho
			S * PDF(d1) * std::sqrt(T),					// Vega
			0.5*S*phiD1*v / std::sqrt(T) - r * K*DF*PhiD2	// Theta
			});

		return metrics;
	}

	double BlackScholesPricer::CDF(const double x) { return 0.5 * std::erfc(-(x * OneOverSqrt2)); }
	double BlackScholesPricer::PDF(const double x) { return std::exp(-0.5 * x*x) * OneOverSqrt2Pi; }

	adept::adouble BlackScholesPricer::CDF(const adept::adouble x) { return 0.5 * adept::erfc(-(x * OneOverSqrt2)); }
	adept::adouble BlackScholesPricer::PDF(const adept::adouble x) { return adept::exp(-0.5 * x*x) * OneOverSqrt2Pi; }

	double S, K, r, v, T;

