#pragma once

#include <include/Products.hpp>
#include <map>
#include <memory>


class ProductFactory
{
public:
	typedef std::shared_ptr<Product>(*ProductConstructor)(std::map<std::string, double>);

	static ProductFactory& Instance()
	{
		static ProductFactory myInstance;
		return myInstance;
	}

	void add(std::string key, ProductConstructor constructor)
	{
		//_constructors.insert(std::make_pair(key, constructor));
		_constructors.emplace(key, constructor);
	}

	static std::shared_ptr<Product> create(const std::string& key, std::map<std::string, double> dictInputs)
	{
		try 
		{
			return (ProductFactory::Instance()._constructors.at(key))(dictInputs);
		}
		catch (const std::out_of_range& oor)
		{
			return nullptr;
		}
	}

private:
	std::map<std::string, ProductConstructor> _constructors;
};

template <class T>
class ProductRegistrator
{
public:
	ProductRegistrator(const std::string& key)
	{
		ProductFactory& factory = ProductFactory::Instance();
		factory.add(key, ProductRegistrator<T>::Create);
	}

	static std::shared_ptr<Product> Create(std::map<std::string, double> dictInputs)
	{
		return std::make_shared<T>(dictInputs);
	}
};