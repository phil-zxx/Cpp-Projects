#pragma once

#include <map>


class Product
{
public:
	virtual double getPrice() const = 0;
};

class Stock : public Product
{
public:
	Stock(const double value)
		: _value(value) { }

	Stock(const std::map<std::string,double>& dictInputs)
		: _value(dictInputs.at("Value")) { }

	double getPrice() const
	{
		return _value;
	}

private:
	double _value;
};

class Future : public Product
{
public:
	Future(const double value, const double strike)
		: _value(value), _strike(strike) { }

	Future(const std::map<std::string, double>& dictInputs)
		: _value(dictInputs.at("Value")) , _strike(dictInputs.at("Strike")) { }

	double getPrice() const
	{
		return _value - _strike;
	}

private:
	double _value, _strike;
};