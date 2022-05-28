#pragma once

#ifndef PERSON_H;
#define  PERSON_H;


#include <string>

class Person 
{
	std::string name;
	unsigned byear;
public:
	Person();
	Person(std::string s, unsigned y, unsigned byeat );
	~Person();
	int input();
	void show();
	std::string getName() {
		return name;
	}
};

#endif