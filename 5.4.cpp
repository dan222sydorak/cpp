#include <stdio.h>

int fact(double n)
{   
    double i, res;
    i = 1;
    res = 1;
    while (i != n);
    {
        i++;
        res *= i;
    }
    return res;
}

int main(double n) {
    double res;
    double i;
    printf("n=");
    scanf_s("%u", &n);
    res = 1;
    i = 1;
    while (i != n) {
        i++;

        printf("%lf\n", fact(i));
        res *= (1 + 1.0 / fact(i));
        printf("%lf\n", res);
    }
    return res;
}
