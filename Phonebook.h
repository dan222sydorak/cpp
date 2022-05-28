#pragma once

#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "Aquainted.h"
#include <cstdlib>
class Phonebook
{
	size_t n;
	Aquainted records[100];
public:
	Phonebook();
	Phonebook(std::string s, unsigned y, unsigned byeat);
	~Phonebook();

	int addRecord(Aquainted& ref);
	std::string findByName(const std::string& name);
	int editPhone(const std::string& name, const std::string& phone);

	int input();
	void show();
};


#endif