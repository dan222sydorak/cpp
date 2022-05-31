#include <iostream>                   
#include <cmath>                      

int main()
{
	double x, y;
	std::cout << "x=";
	std::cin >> x;
	std::cout << "y=";
	std::cin >> y;

	double sum, product;
	sum = x + y;
	product = x * y;
	std::cout << "summa=" << sum << std::endl;
	std::cout << "product=" << product << std::endl;
}