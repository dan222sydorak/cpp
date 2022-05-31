#include <stdio.h>
#include <float.h>

int main() {
    int m;
    int m1;
    scanf_s("%d", &m);
    scanf_s("%d", &m1);

    if (m < 1) {
        printf("incorrect input");
        return 0;
    }

    int p1 = 1, r1 = 0; // p = 2^r
    do {
        p1 *= 2;
        r1++;
    } while (p1 <= m1);
    printf("2^%d > %d", r1, m1);
}