#include <BlackScholesPricer.hpp>
#include <adept_source.h>


adept::Stack stack;

BlackScholesPricer::BlackScholesPricer(double SS, double KK, double rr, double vv, double TT)
    : S(SS), K(KK), r(rr), v(vv), T(TT) { }

double BlackScholesPricer::getPrice()
{
    return calcPrice<double>(S, K, r, v, T);
}

std::vector<double> BlackScholesPricer::getPriceGreeks_Analytical()
{
    return calcPriceGreeks(S, K, r, v, T);
}

std::vector<double> BlackScholesPricer::getPriceGreeks_FD(const double h)
{
    const double basePrice = calcPrice<double>(S, K, r, v, T);

    std::vector<double> metrics({
            basePrice,                                                                                // NPV
            (calcPrice<double>(S + h, K, r, v, T) - calcPrice<double>(S - h, K, r, v, T)) / (2 * h),  // DeltaSpot
            (calcPrice<double>(S, K + h, r, v, T) - calcPrice<double>(S, K - h, r, v, T)) / (2 * h),  // DeltaStrike
            (calcPrice<double>(S, K, r + h, v, T) - calcPrice<double>(S, K, r - h, v, T)) / (2 * h),  // Rho
            (calcPrice<double>(S, K, r, v + h, T) - calcPrice<double>(S, K, r, v - h, T)) / (2 * h),  // Vega
           -(calcPrice<double>(S, K, r, v, T + h) - calcPrice<double>(S, K, r, v, T - h)) / (2 * h)   // Theta
        });

    return metrics;
}

std::vector<double> BlackScholesPricer::getPriceGreeks_AD()
{
    adouble S_AD = S, K_AD = K, r_AD = r, v_AD = v, T_AD = T;

    stack.new_recording();
    const adouble NPV = calcPrice<adouble>(S_AD, K_AD, r_AD, v_AD, T_AD);

    NPV.set_gradient(1.0);
    stack.compute_adjoint();

    std::vector<double> metrics({
            NPV.value(),          // NPV
            S_AD.get_gradient(),  // DeltaSpot
            K_AD.get_gradient(),  // DeltaStrike
            r_AD.get_gradient(),  // Rho
            v_AD.get_gradient(),  // Vega
            -T_AD.get_gradient()  // Theta
        });

    return metrics;
}

double BlackScholesPricer::CDF(const double x)
{
    return 0.5 * std::erfc(-(x * OneOverSqrt2));
}

double BlackScholesPricer::PDF(const double x)
{
    return std::exp(-0.5 * x*x) * OneOverSqrt2Pi;
}

adouble BlackScholesPricer::CDF(const adouble x)
{
    return 0.5 * adept::erfc(-(x * OneOverSqrt2));
}

adouble BlackScholesPricer::PDF(const adouble x)
{
    return adept::exp(-0.5 * x*x) * OneOverSqrt2Pi;
}

std::vector<double> BlackScholesPricer::calcPriceGreeks(double S, double K, double r, double v, double T)
{
    const double sigSqrtT = v * std::sqrt(T);
    const double d1       = (std::log(S / K) + (r + 0.5*v*v)*T) / sigSqrtT;
    const double d2       = d1 - sigSqrtT;
    const double DF       = std::exp(-r * T);
    const double PhiD1    = CDF(d1);
    const double phiD1    = PDF(d1);
    const double PhiD2    = CDF(d2);

    std::vector<double> metrics({
            S * PhiD1 - K * PhiD2 * DF,                     // NPV
            PhiD1,                                          // DeltaSpot
            -DF*PhiD2,                                      // DeltaStrike
            K*T*DF*PhiD2,                                   // Rho
            S * PDF(d1) * std::sqrt(T),                     // Vega
            -0.5*S*phiD1*v / std::sqrt(T) - r * K*DF*PhiD2  // Theta
        });

    return metrics;
}

// template double BlackScholesPricer::calcPrice(double S, double K, double r, double v, double T);
// template adouble BlackScholesPricer::calcPrice(adouble S, adouble K, adouble r, adouble v, adouble T);