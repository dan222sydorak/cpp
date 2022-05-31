cmake_minimum_required(VERSION 3.20)
project(ComplexPoly_CPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(ComplexPoly_CPP main.cpp ComplexPolyP.cpp ComplexPoly_test.cpp ComplexPoly_cross_test.cpp ComplexP.cpp tests.h
        ../ComplexPoly_C/Complex.c ../ComplexPoly_C/ComplexPoly.c)