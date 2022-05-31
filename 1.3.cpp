#include "stdio.h"
#include <iostream>

int main()
{
	float A;
	long float C;
    double B;
	std::cout << "A=";
	std::cin >> A;
	std::cout << "B=";
	std::cin >> B;
	std::cout << "C=";
	std::cin >> C;
	int sum;
	double average;
	double harmon;
	sum = A + B + C;
	std::cout << "Summ A, B, C equal:" << sum << "\n";
	average = (double)(A + B + C) / 3;
	std::cout << "Average of A, B, C equal:" << average << "\n";
	harmon = 3 / ((1 / A) + (1 / B) + (1 / C));
	std::cout << "Harmonic mean of A, B, C equal:" << harmon << "\n";
}