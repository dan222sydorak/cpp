#include "Phonebook.h"
#include "Person.h"

Phonebook::Phonebook()
{
	n = 0;
}

Phonebook::~Phonebook() {}

int Phonebook::addRecord(Aquainted& ref) {
	if (n >= 100) return -1;
	records[n++] = ref;
	return 0;
}

std::string Phonebook::findByName(const std::string& name) {
	for (size_t i = 0; i < n; i++) {
		if (records[i].getName == name) {
			return records[i].getPhone();
		}
	}
	return std::string("None");
}

int Phonebook::editPhone(const std::string& name, const std::string& ph) {
	for (size_t i = 0; i < n; i++) {
		if (records[i].getName() == name) {
			records[i].setPhone(ph);
			return i;
		}
	}
	return -1;
}