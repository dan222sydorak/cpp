#include <stdio.h>
#include <float.h>

int main() {
    int m;
    scanf_s("%d", &m);
    if (m < 1) {
        printf("incorrect input");
        return 0;
    }

    int p = 1, r = 0; // p = 4^r
    while (p < m) {
        p *= 4;
        r++;
    }
    printf("4^%d < %d", r - 1, m);
}