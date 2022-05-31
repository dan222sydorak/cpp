// задача 1

#include <stdio.h>
#include <math.h>
#include <iostream>

int main() 
{
    double m1, m2, r, Y = 6.67, F;// дійсні числа(матимуть дані)    
    scanf_s("%lf", &m1);
    scanf_s("%lf", &m2);
    scanf_s("%lf", &r);

    F = Y * m1 * m2 / (r * r);
    printf("F = %le", F);
}