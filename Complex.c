#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include "Complex.h"

Complex* new_Complex(double Re, double Im) {
    Complex *tmp = (Complex*) malloc(sizeof(Complex));
    set_Complex(tmp, Re, Im);
    return tmp;
}

void set_Complex(Complex *num, double Re, double Im) {
    num->Re = Re;
    num->Im = Im;
}

void free_Complex(Complex *num) {
    if(num) {
        free(num);
    }
}

int equal_Complex(Complex *num1, Complex *num2) {
    return (num1->Re == num2->Re) && (num1->Im == num2->Im);
}

Complex* neg_Complex(Complex *num) {
    return new_Complex(-num->Re, -num->Im);
}

Complex* plus_Complex(Complex *num1, Complex *num2) {
    return new_Complex(num1->Re + num2->Re, num1->Im + num2->Im);
}

Complex* minus_Complex(Complex *num1, Complex *num2) {
    return new_Complex(num1->Re - num2->Re, num1->Im - num2->Im);
}

Complex* mul_Complex(Complex *num1, Complex *num2) {
    double n_Re = num1->Re * num2->Re - num1->Im * num2->Im;
    double n_Im = num1->Re * num2->Im + num1->Im * num2->Re;
    return new_Complex(n_Re, n_Im);
}

Complex* div_Complex(Complex *num1, Complex *num2) {
    if(num2->Re == 0 && num2->Im == 0) return NULL;

    double divisor = num2->Re * num2->Re + num2->Im * num2->Im;
    double n_Re = (num1->Re * num2->Re + num1->Im * num2->Im) / divisor;
    double n_Im = (num1->Im * num2->Re - num1->Re * num2->Im) / divisor;
    return new_Complex(n_Re, n_Im);
}

Complex* power_Complex(Complex *num, int n) {
    Complex *res = new_Complex(1, 0);
    for(int i = 0; i < abs(n); i++) {
        res = mul_Complex(res, num);
    }
    if(n < 0) {
        res = div_Complex(new_Complex(1, 0), res);
    }
    return res;
}

char* ctos(Complex *num) {
    int size = 50;
    char *buff[size];

    snprintf(*buff, size, "%.3f%+.3fi", num->Re, num->Im);
    return *buff;
}

Complex* stoc(char *str) {
    Complex *tmp = new_Complex(0, 0);
    sscanf(str, "%lf%lfi", &tmp->Re, &tmp->Im);
    return tmp;
}

int print_Complex(Complex *num) {
    return printf("%.3f%+.3fi", num->Re, num->Im);
}

void remove_whitespaces() {
    int c;
    while ((c = getchar()) != EOF) {
        if (c != ' ') {
            putchar(c);
        }
        if (c == '\n') {
            break;
        }
    }
}

int input_Complex(Complex *num) {
    remove_whitespaces();
    int res = scanf("%lf%lfi", &num->Re, &num->Im);
    return res;
}

Complex* round_Complex(const Complex *num, int precision) {
    if(precision < 0) return NULL;

    int dec = (int)round(pow(10, precision));
    double n_Re = round(num->Re * dec) / dec;
    double n_Im = round(num->Im * dec) / dec;
    return new_Complex(n_Re, n_Im);
}