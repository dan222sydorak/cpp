// task 3.6

#include <stdio.h>
#include<iostream>

	using namespace std;
	int main() 
	{
		int a, b, c;
		cout << " a=";
		cin >> a;
		cout << " b=";
		cin >> b;
		cout << " c=";
		cin >> c;
		if (a > b && a > c) {
			cout << " the greatest:" << a;
		}
		else if (b > a && b > c) {
			cout << " the greatest" << b;
		}
		else {
			cout << " the  greatest" << c;
		}
		return 0;
	}
