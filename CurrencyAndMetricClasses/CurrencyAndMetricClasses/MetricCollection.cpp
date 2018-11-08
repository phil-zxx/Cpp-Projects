#include <iostream>
#define QP_DEFINE_METRIC(NAME,param) struct NAME{double param;void operator*=(const double& x){ param *= x;}}

using namespace std;

namespace QPricer
{
	struct Metrics
	{
		QP_DEFINE_METRIC(NPV,     npv);
		QP_DEFINE_METRIC(DeltaEq, deltaEq);
		QP_DEFINE_METRIC(GammaEq, gammaEq);
		QP_DEFINE_METRIC(DeltaIr, deltaIr);
		QP_DEFINE_METRIC(Theta,   theta);
	};

	template<class... Ts>
	struct MetricCollection : public Ts...
	{
		MetricCollection()
			: Ts{ 0 } ... { }

		MetricCollection(const double& val)
			: Ts{ val } ... { }

		MetricCollection& operator*=(const double& x)
		{
			(static_cast<Ts&>(*this).operator*=(x), ...);
			return *this;
		}
	};
}


int main()
{
	using namespace QPricer;

	MetricCollection<Metrics::NPV, Metrics::DeltaEq> m1;
	MetricCollection<Metrics::NPV, Metrics::DeltaEq> m2(25);		
	
	m2.npv = 30;
	m2 *= 4;

	return 0;
}