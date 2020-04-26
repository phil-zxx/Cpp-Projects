#include <Products.hpp>


Stock::Stock(const double& value)
    : m_value(value) { }

Stock::Stock(const std::map<std::string,double>& dictInputs)
    : m_value(dictInputs.at("Value")) { }

double Stock::getPrice() const
{
    return m_value;
}

Future::Future(const double& value, const double& strike)
    : m_value(value), m_strike(strike) { }

Future::Future(const std::map<std::string, double>& dictInputs)
    : m_value(dictInputs.at("Value")), m_strike(dictInputs.at("Strike")) { }

double Future::getPrice() const
{
    return m_value - m_strike;
}
