#include <iostream>
#include "Phonebook.h"



int main(int argc, char **argv){

	Phonebook pb;

	size_t n;
	std::cout << "N: ";
	std::cin >> n;
	Aquainted aq;
	for (size_t i = 0; i < n; i++) {
		aq.input();
		pb.addRecord(aq);
	}

	std::string name;
	std::cout << "Name to find:";
	std::cin >> name;

	std::cout << "Tel is:" << pb.findByName(name) << "\n";
	return 0;

}