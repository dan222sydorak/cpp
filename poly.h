#pragma once
#include <iostream>
#include <fstream>
#include <initializer_list>

class Poly {
private:
	unsigned order;
	double* coeffs;
public:
	Poly();
	Poly(const std::initializer_list<double>& lst);
	Poly(const Poly& right);
	~Poly();

	unsigned get_order() const;

	double& operator[](unsigned i) const;
	Poly operator+(const Poly& right);
	Poly operator-(const Poly& right);
	Poly& operator=(const Poly& right);

	void replace(const double* arr, unsigned size);

	friend std::ostream& operator<<(std::ostream& out, const Poly& poly);
	friend std::istream& operator>>(std::istream& in, Poly& poly);

	friend std::ofstream& operator<<(std::ofstream& out, const Poly& poly);
	friend std::ifstream& operator>>(std::ifstream& in, Poly& poly);
};

