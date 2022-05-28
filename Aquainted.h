#pragma once


#ifndef AQUAINTED_H
#define  AQUAINTED_H

#include <string>
#include "Person.h"

class Aquainted : public Person
{
	std::string phone;
public:
	Aquainted();
	Aquainted(const std::string& s, unsigned y, const std::string& ph):
	Person(s, y) {
		phone = ph;

	};
	~Aquainted();
	int input();

	void setPhone(std::string ph);
	std::string getPhone() {
		return phone;
	}
	
};


#endif 