#include <cassert>
#include <iomanip>

#include "ComplexP.h"
#include "ComplexPolyP.h"

#include "tests.h"

// test 1: ComplexP numbers functions
void test_Complex() {
    //checking validity of constructors and in/out
    std::stringstream ss(std::ios_base::app|std::ios_base::in|std::ios_base::out);
    ComplexP tmp1;
    ss << tmp1;
    assert(ss.str() == "0" && "Zero output");

    ss.str("");
    tmp1 = ComplexP(1.34, -1);
    ss << tmp1;
    assert(ss.str() == "1.34-i" && "Negative Im");

    ss.str("-5.64-i");
    ss >> tmp1;
    ss.clear();
    ComplexP tmp2(-5.64, -1);
    assert(tmp1 == tmp2 && "Input check");

    //checking validity of operations
    tmp2 = ComplexP{5.64, 1};
    assert(-tmp1 == tmp2 && "Unary minus");

    ComplexP tmp3;
    assert(tmp1+tmp2==tmp3 && "Adding");

    tmp1 = ComplexP{4.6, 40};
    tmp2 = ComplexP{10,7.79};
    tmp3 = ComplexP{-5.4, 32.21};
    assert(tmp1-tmp2==tmp3 && "Subtracting");

    tmp1 = ComplexP{2, 3};
    tmp2 = ComplexP{5, -3};
    tmp3 = ComplexP{19, 9};
    assert(tmp1*tmp2==tmp3 && "Multiplying1");

    tmp1 = ComplexP{};
    tmp2 = ComplexP{5, -3};
    tmp3 = ComplexP{};
    assert(tmp1*tmp2==tmp3 && "Multiplying2");

    tmp1 = ComplexP{5, 4};
    tmp2 = ComplexP{1, 1};
    tmp3 = ComplexP{4.5, -0.5};
    assert(tmp1/tmp2==tmp3 && "Dividing1");

    bool flag = false;
    tmp1 = ComplexP{1, -1};
    tmp2 = ComplexP{};

    try {
        ComplexP tmp4 = tmp1 / tmp2;
    } catch(...) {
        flag = true;
    }
    assert(flag && "Dividing2");

    tmp1 = ComplexP{2, -3};
    tmp2 = ComplexP{-46, -9};
    assert((tmp1^3)==tmp2 && "Power1");
    tmp2 = ComplexP{-5, 12} / 169;
    assert((tmp1^-2)==tmp2 && "Power2");

    ss.str("");
    tmp1 = ComplexP{1.34532, -0.876315};
    tmp1 = round(tmp1, 2);
    ss << tmp1;
    assert(ss.str() == "1.35-0.88i" && "Round");

    std::cout << "100% >> Passed ComplexP tests" << std::endl;
}

//test 2: ComplexPolyP
void test_ComplexPoly() {
    //checking constructors and resizing functions
    ComplexPolyP tmp1(5);
    assert(tmp1.size()==5 && "Size1");
    tmp1.resize(10);
    assert(tmp1.size()==10 && "Size2");

    bool flag = false;
    try {
        tmp1.resize(-10);
    } catch(...) {
        flag = true;
    }
    assert(flag && "Wrong resize");

    // checking access and const access to coefficients
    ComplexP ctmp1 = ComplexP{1, -1};
    tmp1[0] = ctmp1;
    assert(tmp1[0] == ctmp1 && "Straight access");

    flag = false;
    try {
        tmp1[100];
    } catch(...) {
        flag = true;
    }
    assert(flag && "Out of size access");

    ComplexP ctmp2 = ComplexP{2, -3};
    tmp1.at(0) = ctmp2;
    assert(tmp1[0] == ctmp1 && "Const access");

    // scaling by offset => multiplying by x^offset
    int offset = 5;
    ctmp1 = 1;
    tmp1[0] = ctmp1;
    tmp1 = tmp1.scale(offset);
    assert(tmp1[offset] == ctmp1 && "Scale1");
    // returning to base condition
    offset = -5;
    tmp1 = tmp1.scale(offset);
    assert(tmp1[0] == ctmp1 && "Scale2");

    // clearing redundant zeros
    ComplexPolyP tmp2(10);
    int real_size = 4;
    tmp2[real_size-1] = 1;
    tmp2.fit();
    assert(tmp2.size() == real_size && "Fit");

    // value in specific point and derivative
    tmp1 = ComplexPolyP(3);
    tmp1[0] = 1;
    tmp1[1] = 2;
    tmp1[2] = 1;
    assert(tmp1.value(0) == 1 && "Value1");
    assert(tmp1.value(-1) == 0 && "Value2");
    assert(tmp1.value(10) == 121 && "Value3");

    tmp1 = tmp1.derivative();
    tmp2 = ComplexPolyP(2);
    tmp2[0] = 2;
    tmp2[1] = 2;
    assert(tmp1 == tmp2 && "Derivative of func x^2+2x+1");

    tmp1 = ComplexPolyP(1);
    tmp1[0] = 1;
    tmp1 = tmp1.derivative();
    assert(tmp1[0] == 0 && "Derivative of constant");

    // newton method to evaluate the nearest root
    tmp1 = ComplexPolyP(3);
    tmp1[0] = 1;
    tmp1[1] = 2;
    tmp1[2] = 1;
    ctmp1 = 10;
    assert(round(tmp1.root_Newton(ctmp1)) == -1 && "Newton root");


    //checking validity of in/out
    std::stringstream ss;
    tmp1 = ComplexPolyP(3);
    ss << tmp1;
    assert(ss.str() == "0" && "Zero output");

    ss.str("");
    tmp1[0] = ComplexP{4, -2.4};
    tmp1[1] = ComplexP{-3, 2};
    tmp1[2] = ComplexP{1};
    ss << tmp1;
    assert(ss.str() == "4-2.4i + (-3+2i) * x + x^2" && "Poly output");

    tmp1.fprint("test.txt", 1, 0);
    std::fstream fs("test.txt", std::ios::in);
    std::string stmp1, stmp2;
    for(int i = 0; i < tmp1.size(); i++) {
        std::getline(fs, stmp1);
        stmp2 = ctos(round(tmp1[i]));
        assert(stmp1 == stmp2 && "File output");
    }

    // Fast Fourier Transform
    tmp1 = ComplexPolyP(4);
    tmp1[0] = ComplexP{-1};
    tmp1[1] = ComplexP{2};
    tmp1[2] = ComplexP{3};

    tmp2 = ComplexPolyP(4);
    tmp2[0] = ComplexP{4};
    tmp2[1] = ComplexP{-4, 2};
    tmp2[2] = ComplexP{0};
    tmp2[3] = ComplexP{-4, -2};
    ComplexPolyP tmp3 = tmp1.fft();
    assert(tmp3 == tmp2 && "fft");
    tmp3 = tmp3.inverse_fft();
    tmp3.resize(tmp1.size());
    assert(tmp3 == tmp1 && "inverse_fft");

    // Reciprocal poly
    tmp1 = ComplexPolyP(4);
    tmp1[0] = ComplexP{0};
    tmp1[1] = ComplexP{1};
    tmp1[2] = ComplexP{3};
    tmp1[3] = ComplexP{1};

    tmp2 = ComplexPolyP(4);
    tmp2[0] = ComplexP{-21};
    tmp2[1] = ComplexP{8};
    tmp2[2] = ComplexP{-3};
    tmp2[3] = ComplexP{1};
    assert(tmp1.recip() ==  tmp2 && "Poly reciprocal");

    // operation functions
    tmp1 = ComplexPolyP(4);
    tmp1[0] = ComplexP{0};
    tmp1[1] = ComplexP{1};
    tmp1[2] = ComplexP{3};
    tmp1[3] = ComplexP{1};

    tmp2 = ComplexPolyP(3);
    tmp2[0] = ComplexP{-21};
    tmp2[1] = ComplexP{8};
    tmp2[2] = ComplexP{-3};

    tmp3 = ComplexPolyP(4);
    tmp3[0] = ComplexP{-21};
    tmp3[1] = ComplexP{9};
    tmp3[2] = ComplexP{0};
    tmp3[3] = ComplexP{1};
    assert(tmp3 == tmp1 + tmp2 && "Adding");

    tmp3 = ComplexPolyP(4);
    tmp3[0] = ComplexP{21};
    tmp3[1] = ComplexP{-7};
    tmp3[2] = ComplexP{6};
    tmp3[3] = ComplexP{1};
    assert(tmp3 == tmp1 - tmp2 && "Subtracting");

    tmp1 = ComplexPolyP(2);
    tmp1[0] = ComplexP{1};
    tmp1[1] = ComplexP{1};

    tmp2 = ComplexPolyP(2);
    tmp2[0] = ComplexP{-1};
    tmp2[1] = ComplexP{1};

    tmp3 = tmp1 * tmp2;

    ComplexPolyP tmp4 = ComplexPolyP(3);
    tmp4[0] = ComplexP{-1};
    tmp4[1] = ComplexP{};
    tmp4[2] = ComplexP{1};
    tmp4.fprint("test.txt");
    assert(tmp3 == tmp4 && "Multiplying");
    assert(tmp3 / tmp2 == tmp1 && "Dividing");

//    tmp4[0] = ComplexP{};
//    tmp4[1] = ComplexP{};
//    tmp4[2] = ComplexP{};
//    std::cin >> tmp4;
//    std::cout << tmp4;

    std::cout << "100% >> Passed ComplexPolyP tests" << std::endl;
}