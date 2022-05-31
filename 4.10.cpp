#include <stdio.h>
#include <float.h>

int main() {

    double eps = 1.0;
    int k = 0;
    do {
        eps = eps / 2;
        k++;
    } while (1.0 + eps != 1.0);

    printf("k=%d zeros=%g, %g", k, eps * 2, DBL_EPSILON);
}