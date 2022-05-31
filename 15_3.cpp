#include <iostream>
#include <cstdio>


#include "Poly.h"

Poly::Poly(size_t n_) {
	n = n_;
	a = new PTYPE[n + 1];
}

Poly::Poly(size_t n_, PTYPE* arr) {
	n = n_;
	a = new PTYPE[n + 1];
	for (int i = 0; i <= n; i++) {
		a[i] = arr[i];
	}
}


void Poly::setPoly(size_t n_, PTYPE* arr) // setter
{
	n = n_;
	for (int i = 0; i <= n; i++) {
		a[i] = arr[i];
	}

}
void Poly::setCoef(size_t k, PTYPE a_) {
	if (k > n) {
		std::cerr << k << "is greater than " << n << ",error!\n";
	}
	a[k] = a_;
}

void Poly::show() {
	if (n == 0) {
		std::cout << "empty";
		return;
	}
	std::cout << a[0] << "x^" << n;
	for (int i = 1; i < n; ++i) {
		if (a[i] < 0)
			std::cout << a[i] << "x^" << (n - i);
		else
			std::cout << "+" << a[i] << "x^" << (n - i);
	}
	if (n == 1) return;
	if (a[n] < 0)
		std::cout << a[n] << "\n";
	else
		std::cout << "+" << a[n] << "\n";
}

PTYPE Poly::value(PTYPE x) {
	PTYPE v = a[0];
	for (int i = 1; i <= n; ++i) {
		v = v * x + a[i];
	}
	return v;
}

int inputFromFile(const char* fname, Poly& p) {
	FILE* fp = fopen(fname, "rb");
	if (fp == NULL) return -1;
	size_t m;
	int r = fread(&m, sizeof(m), 1, fp);
	std::clog << m;
	if (r != 1) return -2;
	Poly* p1 = new Poly(m);
	r = fread(p1->a, sizeof(PTYPE), m + 1, fp);
	fclose(fp);
	if (r != m + 1) {
		return -3;
	}
	p = *p1;
	delete p1;

	return 0;
}

int outputToFile(const char* fname, const Poly& p) {

	FILE* fp = fopen(fname, "wb");
	if (fp == NULL) return -1;

	int r = fwrite(&p.n, sizeof(p.n), 1, fp);
	std::clog << "n=" << p.n << "\n";
	if (r != 1) {
		fclose(fp);
		return -2;
	}

	r = fwrite(p.a, sizeof(PTYPE), p.n + 1, fp);
	fclose(fp);
	if (r != p.n + 1) {
		return -3;
	}

	return 0;
}


int main() {

	Poly p1;
	Poly p2(3);

	PTYPE mas[] = { 1.0,2.0,3.5 };
	Poly p3(2, mas);
	Poly p4(p2);

	p2.setPoly(2, mas);

	p3.show();
	p2.setCoef(2, 2.0);
	p2.show();
	std::cout << p3.value(1);

	p1 = p2;
	p1.show();
	p3 = p1;
	p3.show();
	p1 = p2;
	p1.value(1.0);
	p1.show();
	p1.setCoef(1, 0.0);

	outputToFile("p1.dat", p2);
	Poly p5;
	inputFromFile("p1.dat", p5);
	p5.show();
}