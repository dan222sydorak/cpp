#include <cassert>
#include "ComplexPolyP.h"
#include "tests.h"

extern "C" {
#include "../ComplexPoly_C/ComplexPoly.h"
}

void cross_test() {
    ComplexPolyP poly1(2);
    poly1[0] = 1;
    poly1[1] = 1;

    ComplexPolyP poly2(2);
    poly2[0] = -1;
    poly2[1] = 1;

    ComplexPolyP poly3 = poly1 * poly2;

    ComplexPoly *cpoly1 = new_ComplexPoly(2);
    set_coefficient(cpoly1, 0, new_Complex(1, 0));
    set_coefficient(cpoly1, 1, new_Complex(1, 0));

    ComplexPoly *cpoly2 = new_ComplexPoly(2);
    set_coefficient(cpoly2, 0, new_Complex(-1, 0));
    set_coefficient(cpoly2, 1, new_Complex(1, 0));

    ComplexPoly *cpoly3 = mul_ComplexPoly(cpoly1, cpoly2);

    assert(size(cpoly3) == poly3.size());

    for(int i = 0; i < poly3.size(); i++) {
        assert(poly3[i].Re == get_coefficient(cpoly3, i)->Re &&
               poly3[i].Im == get_coefficient(cpoly3, i)->Im);
    }

    poly1 = poly3 / poly2;
    cpoly1 = div_ComplexPoly(cpoly3, cpoly2);

    assert(size(cpoly1) == poly1.size());

    for(int i = 0; i < poly1.size(); i++) {
        assert(poly1[i].Re == get_coefficient(cpoly1, i)->Re &&
               poly1[i].Im == get_coefficient(cpoly1, i)->Im);
    }

    std::cout << "100% >> Passed cross-test" << std::endl;
}