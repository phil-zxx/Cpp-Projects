#include <iostream>
#include <functional>
#include <string>

using namespace std;


class Solver
{
public:

	static double solve(const std::function<double(double)>& f, const std::function<double(double)>& deriv, const double& xGuess = 0.15)
	{
		const double eps = 1.e-8;

		double x = xGuess, y = f(xGuess), dx = y / deriv(xGuess);

		while (std::abs(dx) > eps)
		{
			x -= dx;
			y  = f(x);
			dx = y / deriv(x);
		}
		return x;
	}
};

double BSPrice(const double& S, const double& K, const double& v)
{
	return (S - K)*v*v + v;
}


int main()
{
	double S = 100, K = 90;
	double price = 12;

	const std::function<double(double)> fPrice = { [&](double x) {
		return BSPrice(S, K, x) - price;
	} };

	const std::function<double(double)> fDeriv = { [&](double x) {
		const double h = 0.00001;
		return (fPrice(x + h) - fPrice(x)) / h;
		}};

	cout << Solver::solve(fPrice, fDeriv) << endl;

	return 0;
}