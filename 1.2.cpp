#include "stdio.h"
#include <iostream>
using namespace std;

int main()
{
	double x;
	cin >> x;
	long long int y1 = x / 10000000000;
	long long int y2 = x - (double)y1 * 10000000000;
	cout << y1 + y2;
}