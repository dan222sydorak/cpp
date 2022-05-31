#include <iostream>                   
#include <cmath>                      

int main()
{
	double x, y;
	std::cout << "x=";
	std::cin >> x;
	std::cout << "y=";
	std::cin >> y;

	double average, harmonic;
	average = (x + y)/2;
	harmonic = x * y/(1/x+1/y);
	std::cout << "average=" << average << std::endl;
	std::cout << "harmonic=" << harmonic << std::endl;
}