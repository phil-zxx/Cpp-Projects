#include <iostream>

#include <ProductFactory.hpp>


int main()
{
    ProductRegistrator<Stock>("Stock");
    ProductRegistrator<Future>("Future");

    std::map<std::string, double> stockData { {"Value", 100} };
    std::map<std::string, double> futureData{ {"Value", 110}, {"Strike", 30} };

    std::shared_ptr<Product> stock  = ProductFactory::create("Stock", stockData);
    std::shared_ptr<Product> future = ProductFactory::create("Future", futureData);

    std::cout << stock->getPrice() << std::endl;
    std::cout << future->getPrice() << std::endl;

    return 0;
}