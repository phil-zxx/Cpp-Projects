#include <include/ProductFactory.hpp>


std::shared_ptr<Product> ProductFactory::create(const std::string& key, const std::map<std::string, double>& dictInputs)
{
    try
    {
        return (ProductFactory::Instance().m_constructors.at(key))(dictInputs);
    }
    catch (const std::out_of_range&)
    {
        return nullptr;
    }
}

ProductFactory& ProductFactory::Instance()
{
    static ProductFactory myInstance;
    return myInstance;
}

void ProductFactory::addConstructor(std::string key, ProductConstructor constructor)
{
    ProductFactory::Instance().m_constructors.emplace(key, constructor);
}
