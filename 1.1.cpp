#include "stdio.h"
#include <iostream>

int main()
{
	double C,F; 
	std::cout << "C=";
	std::cin >> C;
	F = 9 * C / 5 + 32;
	std::cout << "F=" << F; //вывод на экран значения переменной F
	return 0;
}