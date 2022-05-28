#pragma once
#include <iostream>
#include <exception>
#include <cmath>

struct division_by_zero_exception : public std::exception {
	const char* what() const {
		return "Division by zero";
	}
};

using rational_exception = division_by_zero_exception;

class Rational {
private:
	int nominator;
	unsigned denominator;

	void cut();
public:
	Rational();
	Rational(int n, unsigned d) throw(division_by_zero_exception);

	int get_nominator() const;
	void set_nominator(int nominator);

	int get_denominator() const;
	void set_denominator(unsigned denominator) throw(division_by_zero_exception);
	
	double value() const;

	Rational operator+(const Rational& right);
	Rational operator-(const Rational& right);
	Rational operator*(const Rational& right);

	bool operator<(const Rational& right);
	bool operator>(const Rational& right);
	bool operator==(const Rational& right);
	bool operator!=(const Rational& right);

	friend std::ostream& operator<<(std::ostream& out, const Rational& rational);
	friend std::istream& operator>>(std::istream& in, Rational& rational) throw(division_by_zero_exception);
};

Rational abs(const Rational& right);

