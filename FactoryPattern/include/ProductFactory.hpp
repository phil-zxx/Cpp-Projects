#pragma once

#include <Products.hpp>
#include <map>
#include <stdexcept>
#include <memory>


class ProductFactory
{
public:
    static std::shared_ptr<Product> create(const std::string& key, const std::map<std::string, double>& dictInputs);

private:
    using ProductConstructor = std::shared_ptr<Product>(*)(const std::map<std::string, double>&);

    static ProductFactory& Instance();
    static void addConstructor(std::string key, ProductConstructor constructor);

    std::map<std::string, ProductConstructor> m_constructors;

    template <class T>
    friend class ProductRegistrator;
};

template <class T>
class ProductRegistrator
{
public:
    explicit ProductRegistrator(const std::string& key);

private:
    static std::shared_ptr<Product> invokeConstructor(const std::map<std::string, double>& dictInputs);
};


// Inline Definitions

template <class T>
inline ProductRegistrator<T>::ProductRegistrator(const std::string& key)
{
    ProductFactory& factory = ProductFactory::Instance();
    ProductFactory::addConstructor(key, ProductRegistrator<T>::invokeConstructor);
}

template <class T>
inline std::shared_ptr<Product> ProductRegistrator<T>::invokeConstructor(const std::map<std::string, double>& dictInputs)
{
    return std::make_shared<T>(dictInputs);
}