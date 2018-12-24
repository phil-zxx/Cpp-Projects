#include <iostream>
#include <chrono>

#include <Currency.hpp>
#include <MetricCollection.hpp>


int main()
{
    //
    // Currency Test
    //

    const size_t n        = 100'000'000;
    const double nano     = 1'000'000'000.;
    const char ccyCode[4] = "EUR";
    const int ccyHash     = 5147843;
    size_t i;

    auto startTime1 = std::chrono::high_resolution_clock::now();
    for (i = 0; i < n; ++i)
        CurrencyChar ccy1(ccyCode);
    auto endTime1 = std::chrono::high_resolution_clock::now();
    std::cout << (endTime1 - startTime1).count() / nano << "\n";

    auto startTime2 = std::chrono::high_resolution_clock::now();
    for (i = 0; i < n; ++i)
        CurrencyInt ccy2(ccyHash);
    auto endTime2 = std::chrono::high_resolution_clock::now();
    std::cout << (endTime2 - startTime2).count() / nano << "\n";


    //
    // Metric Collection Test
    //

    MetricCollection<Metrics::NPV, Metrics::DeltaEq> m1;
    MetricCollection<Metrics::NPV, Metrics::DeltaEq> m2(25);

    m2.npv = 30;
    m2 *= 4;

    return 0;
}