#include <iostream>

#define QP_DEFINE_METRIC(NAME,param) struct NAME{double param;void operator*=(const double& x){ param *= x;}}


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
	MetricCollection();
    explicit MetricCollection(const double& val);

	MetricCollection& operator*=(const double& x);
};


// Inline Definitions

template<class... Ts>
MetricCollection<Ts...>::MetricCollection()
    : Ts{ 0 } ... { }

template<class... Ts>
MetricCollection<Ts...>::MetricCollection(const double& val)
    : Ts{ val } ... { }

template<class... Ts>
MetricCollection<Ts...>& MetricCollection<Ts...>::operator*=(const double& x)
{
    (static_cast<Ts&>(*this).operator*=(x), ...);
    return *this;
}