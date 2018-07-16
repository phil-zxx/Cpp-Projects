#include <iostream>

#include <include/ProductFactory.hpp>


using namespace std;

int main()
{
	ProductRegistrator<Stock>("Stock");
	ProductRegistrator<Future>("Future");
	ProductFactory::add("Stock", std::make_shared<Stock>);

	std::map<std::string, double> inputs1{ {"Value", 100} };
	std::shared_ptr<Product> prodStock = ProductFactory::create("Stock", inputs1);

	std::map<std::string, double> inputs2{ { "Value", 110 }, { "Strike", 30 } };
	std::shared_ptr<Product> prodFuture = ProductFactory::create("Future", inputs2);

	cout << prodStock->getPrice() << endl;
	cout << prodFuture->getPrice() << endl;

	return 0;
}