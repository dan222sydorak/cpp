#include <iostream>
#include <cmath>

float calculatePol(int x)
{
	int y;
	y = pow(x, 5) + 5 * pow(x, 4) + 10 * pow(x, 2) + 5 * x + 1;

	return(y);
}

void main()
{
	int x, l;
	std::cout << "enter x:";
	std::cin >> x;
	l = calculatePol(x);
	std::cout << l;
}