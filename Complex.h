#ifndef COMPLEXPOLY_C_COMPLEX_H
#define COMPLEXPOLY_C_COMPLEX_H

typedef struct Complex{
    double Re;
    double Im;
} Complex;

Complex* new_Complex(double Re, double Im);
void set_Complex(Complex *num, double Re, double Im);
void free_Complex(Complex *num);

int equal_Complex(Complex *num1, Complex *num2);

Complex* neg_Complex(Complex *num);
Complex* plus_Complex(Complex *num1, Complex *num2);
Complex* minus_Complex(Complex *num1, Complex *num2);
Complex* mul_Complex(Complex *num1, Complex *num2);
Complex* div_Complex(Complex *num1, Complex *num2);
Complex* power_Complex(Complex *num, int n);

char* ctos(Complex *num);
Complex* stoc(char *str);

int print_Complex(Complex *num);
int input_Complex(Complex *num);

Complex* round_Complex(const Complex *num, int precision);

#endif //COMPLEXPOLY_C_COMPLEX_H
