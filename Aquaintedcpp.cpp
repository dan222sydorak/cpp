#include <iostream>
#include "Aquainted.h"

Aquainted::Aquainted(){}

Aquainted::~Aquainted() {}

int Aquainted::input(){
	Person::input();
	std::cout << "Phone:";
	std::cin >> phone;
	return 0;
}