#include <stdio.h>
#include <math.h>

int main() {
    int i;
    int n;
    float y;
    printf("x:");
    scanf_s("%f", &x);
    printf("n:");
    scanf_s("%d", &n);
    for (i = 0; i < n; i = i + 1) {
        y += i*pow(x,i);
    }
    printf("y=%lf,y");
}