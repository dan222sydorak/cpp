// задача 2 0<x<100 y=x^8

#include <stdio.h>
#include <math.h>
int main()
{
    double x, y; // дійсні числа(матимуть дані)
    scanf_s("%lf", &x);
    printf("%lf", pow(x, 2)*pow(x,2));
    return 0;
}