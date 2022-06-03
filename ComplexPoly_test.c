#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "Complex.h"
#include "ComplexPoly.h"

void test_Complex() {
//checking validity of constructors and in/out
//    char* buffer = NULL;
//    size_t bufferSize = 0;
//    FILE* myStream = open_memstream();
//    Complex tmp1;
//    ss << tmp1;
//    assert(ss.str() == "0" && "Zero output");
//
//    ss.str("");
//    tmp1 = Complex(1.34, -1);
//    ss << tmp1;
//    assert(ss.str() == "1.34-i" && "Negative Im");
//
//    ss.str("-5.64-i");
//    ss >> tmp1;
//    ss.clear();
//    Complex tmp2(-5.64, -1);
//    assert(tmp1 == tmp2 && "Input check");

    //checking validity of operations
    Complex *tmp1 = new_Complex(-5.64, -1);
    Complex *tmp2 = new_Complex(5.64, 1);
    assert(equal_Complex(neg_Complex(tmp1), tmp2) && "Unary minus");

    Complex *tmp3 = new_Complex(0, 0);
    assert(equal_Complex(plus_Complex(tmp1,tmp2), tmp3) && "Adding");

    tmp1 = new_Complex(4.6, 40);
    tmp2 = new_Complex(10,7.79);
    tmp3 = new_Complex(-5.4, 32.21);
    assert(equal_Complex(minus_Complex(tmp1,tmp2), tmp3) && "Subtracting");

    tmp1 = new_Complex(2, 3);
    tmp2 = new_Complex(5, -3);
    tmp3 = new_Complex(19, 9);
    assert(equal_Complex(mul_Complex(tmp1,tmp2), tmp3) && "Multiplying1");

    tmp1 = new_Complex(0, 0);
    tmp2 = new_Complex(5, -3);
    tmp3 = new_Complex(0, 0);
    assert(equal_Complex(mul_Complex(tmp1,tmp2), tmp3) && "Multiplying2");

    tmp1 = new_Complex(5, 4);
    tmp2 = new_Complex(1, 1);
    tmp3 = new_Complex(4.5, -0.5);
    assert(equal_Complex(div_Complex(tmp1,tmp2), tmp3) && "Dividing1");

    tmp1 = new_Complex(1, -1);
    tmp2 = new_Complex(0, 0);

    assert(div_Complex(tmp1,tmp2) == NULL && "Dividing2");

    tmp1 = new_Complex(2, -3);
    tmp2 = new_Complex(-46, -9);
    assert(equal_Complex(power_Complex(tmp1, 3), tmp2) && "Power1");
    tmp2 = div_Complex(new_Complex(-5, 12), new_Complex(169, 0));
    assert(equal_Complex(power_Complex(tmp1,-2), tmp2) && "Power2");

//    ss.str("");
//    tmp1 = Complex{1.34532, -0.876315};
//    tmp1 = round(tmp1, 2);
//    ss << tmp1;
//    assert(ss.str() == "1.35-0.88i" && "Round");

    printf("100%% >> Passed Complex tests\n");
}

void test_ComplexPoly() {
    //checking constructors and resizing functions
    ComplexPoly *tmp1 = new_ComplexPoly(5);
    assert(size(tmp1)==5 && "Size1");
    resize_ComplexPoly(tmp1, 10);
    assert(size(tmp1)==10 && "Size2");

    assert(!resize_ComplexPoly(tmp1, -10) && "Wrong resize");

    // checking access and const access to coefficients
    Complex *ctmp1 = new_Complex(1, -1);
    set_coefficient(tmp1, 0, ctmp1);
    assert(equal_Complex(get_coefficient(tmp1, 0), ctmp1) && "Straight access");


    assert(get_coefficient(tmp1, 100) == NULL && "Out of size access");

    // scaling by offset => multiplying by x^offset
    int offset = 5;
    set_Complex(ctmp1, 1, 0);
    set_coefficient(tmp1, 0, ctmp1);
    tmp1 = scale(tmp1, offset);
    assert(equal_Complex(get_coefficient(tmp1, offset), ctmp1) && "Scale1");
    // returning to base condition
    offset = -5;
    tmp1 = scale(tmp1, offset);
    assert(equal_Complex(get_coefficient(tmp1, 0), ctmp1) && "Scale2");

    // clearing redundant zeros
    ComplexPoly *tmp2 = new_ComplexPoly(10);
    int real_size = 4;
    set_coefficient(tmp2, real_size-1, new_Complex(1, 0));
    fit(tmp2);
    assert(size(tmp2) == real_size && "Fit");

    // value in specific point and derivative
    tmp1 = new_ComplexPoly(3);
    set_coefficient(tmp1, 0, new_Complex(1, 0));
    set_coefficient(tmp1, 1, new_Complex(2, 0));
    set_coefficient(tmp1, 2, new_Complex(1, 0));
    assert(equal_Complex(value(tmp1, new_Complex(0, 0)), new_Complex(1, 0)) && "Value1");
    assert(equal_Complex(value(tmp1, new_Complex(-1, 0)), new_Complex(0, 0)) && "Value2");
    assert(equal_Complex(value(tmp1, new_Complex(10, 0)), new_Complex(121, 0)) && "Value3");

    tmp1 = derivative(tmp1);
    tmp2 = new_ComplexPoly(2);
    set_coefficient(tmp2, 0, new_Complex(2, 0));
    set_coefficient(tmp2, 1, new_Complex(2, 0));
    assert(equal_ComplexPoly(tmp1, tmp2) && "Derivative of func x^2+2x+1");

    tmp1 = new_ComplexPoly(1);
    set_coefficient(tmp1, 0, new_Complex(1, 0));
    tmp1 = derivative(tmp1);
    assert(equal_Complex(get_coefficient(tmp1, 0), new_Complex(0, 0)) && "Derivative of constant");

    // newton method to evaluate the nearest root
    tmp1 = new_ComplexPoly(3);
    set_coefficient(tmp1, 0, new_Complex(1, 0));
    set_coefficient(tmp1, 1, new_Complex(2, 0));
    set_coefficient(tmp1, 2, new_Complex(1, 0));
    ctmp1 = new_Complex(10, 0);
    assert(equal_Complex(round_Complex(root_Newton(tmp1, ctmp1), 0), new_Complex(-1, 0)) && "Newton root");


    //checking validity of in/out
//    std::stringstream ss;
//    tmp1 = ComplexPoly(3);
//    ss << tmp1;
//    assert(ss.str() == "0" && "Zero output");
//
//    ss.str("");
//    tmp1[0] = Complex{4, -2.4};
//    tmp1[1] = Complex{-3, 2};
//    tmp1[2] = Complex{1};
//    ss << tmp1;
//    assert(ss.str() == "4-2.4i + (-3+2i) * x + x^2" && "Poly output");
//
//    tmp1.fprint("test.txt", 1, 0);
//    std::fstream fs("test.txt", std::ios::in);
//    std::string stmp1, stmp2;
//    for(int i = 0; i < tmp1.size(); i++) {
//        std::getline(fs, stmp1);
//        stmp2 = ctos(round(tmp1[i]));
//        assert(stmp1 == stmp2 && "File output");
//    }

    // Fast Fourier Transform
    tmp1 = new_ComplexPoly(4);
    set_coefficient(tmp1, 0, new_Complex(-1, 0));
    set_coefficient(tmp1, 1, new_Complex(2, 0));
    set_coefficient(tmp1, 2, new_Complex(3, 0));
    set_coefficient(tmp1, 3, new_Complex(0, 0));

    tmp2 = new_ComplexPoly(4);
    set_coefficient(tmp2, 0, new_Complex(4, 0));
    set_coefficient(tmp2, 1, new_Complex(-4, 2));
    set_coefficient(tmp2, 2, new_Complex(0, 0));
    set_coefficient(tmp2, 3, new_Complex(-4, -2));
    ComplexPoly *tmp3 = fft(tmp1);
    assert(equal_ComplexPoly(tmp3, tmp2) && "fft");
    tmp3 = inverse_fft(tmp3);
    resize_ComplexPoly(tmp3, size(tmp1));
    assert(equal_ComplexPoly(tmp3, tmp1) && "inverse_fft");

    // Reciprocal poly
    tmp1 = new_ComplexPoly(4);
    set_coefficient(tmp1, 0, new_Complex(0, 0));
    set_coefficient(tmp1, 1, new_Complex(1, 0));
    set_coefficient(tmp1, 2, new_Complex(3, 0));
    set_coefficient(tmp1, 3, new_Complex(1, 0));

    tmp2 = new_ComplexPoly(4);
    set_coefficient(tmp2, 0, new_Complex(-21, 0));
    set_coefficient(tmp2, 1, new_Complex(8, 0));
    set_coefficient(tmp2, 2, new_Complex(-3, 0));
    set_coefficient(tmp2, 3, new_Complex(1, 0));
    tmp3 = recip(tmp1);
    assert(equal_ComplexPoly(tmp3, tmp2) && "Poly reciprocal");

    // operation functions
    tmp1 = new_ComplexPoly(4);
    set_coefficient(tmp1, 0, new_Complex(0, 0));
    set_coefficient(tmp1, 1, new_Complex(1, 0));
    set_coefficient(tmp1, 2, new_Complex(3, 0));
    set_coefficient(tmp1, 3, new_Complex(1, 0));

    tmp2 = new_ComplexPoly(3);
    set_coefficient(tmp2, 0, new_Complex(-21, 0));
    set_coefficient(tmp2, 1, new_Complex(8, 0));
    set_coefficient(tmp2, 2, new_Complex(-3, 0));

    tmp3 = new_ComplexPoly(4);
    set_coefficient(tmp3, 0, new_Complex(-21, 0));
    set_coefficient(tmp3, 1, new_Complex(9, 0));
    set_coefficient(tmp3, 2, new_Complex(0, 0));
    set_coefficient(tmp3, 3, new_Complex(1, 0));
    assert(equal_ComplexPoly(tmp3, plus_ComplexPoly(tmp1, tmp2)) && "Adding");

    tmp3 = new_ComplexPoly(4);
    set_coefficient(tmp3, 0, new_Complex(21, 0));
    set_coefficient(tmp3, 1, new_Complex(-7, 0));
    set_coefficient(tmp3, 2, new_Complex(6, 0));
    set_coefficient(tmp3, 3, new_Complex(1, 0));
    assert(equal_ComplexPoly(tmp3, minus_ComplexPoly(tmp1, tmp2)) && "Subtracting");

    tmp1 = new_ComplexPoly(2);
    set_coefficient(tmp1, 0, new_Complex(1, 0));
    set_coefficient(tmp1, 1, new_Complex(1, 0));

    tmp2 = new_ComplexPoly(2);
    set_coefficient(tmp2, 0, new_Complex(-1, 0));
    set_coefficient(tmp2, 1, new_Complex(1, 0));

    tmp3 = mul_ComplexPoly(tmp1, tmp2);

    ComplexPoly *tmp4 = new_ComplexPoly(3);
    set_coefficient(tmp4, 0, new_Complex(-1, 0));
    set_coefficient(tmp4, 1, new_Complex(0, 0));
    set_coefficient(tmp4, 2, new_Complex(1, 0));
    assert(equal_ComplexPoly(tmp3, tmp4) && "Multiplying");
    assert(equal_ComplexPoly(div_ComplexPoly(tmp3, tmp2), tmp1) && "Dividing");

    free_ComplexPoly(tmp1);
    free_ComplexPoly(tmp2);
    free_ComplexPoly(tmp3);
    free_ComplexPoly(tmp4);
    free_Complex(ctmp1);

    printf("100%% >> Passed ComplexPoly tests\n");
}