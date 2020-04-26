#pragma once

#include <map>
#include <string>


class Product
{
public:
    virtual double getPrice() const = 0;
};

class Stock : public Product
{
public:
    explicit Stock(const double& value);
    explicit Stock(const std::map<std::string,double>& dictInputs);

    double getPrice() const override;

private:
    const double m_value;
};


class Future : public Product
{
public:
    Future(const double& value, const double& strike);
    explicit Future(const std::map<std::string, double>& dictInputs);

    double getPrice() const override;

private:
    const double m_value, m_strike;
};