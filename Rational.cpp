
#include "Rational.h"

int inputRational(Rational* x) {
    printf("chiselnuk:");
    scanf_s(" %d", &x->numerator);
    printf("znamennyk:");
    scanf_s(" %u", &x->denominator);
    if (x->denominator == 0) return -1;
    return 0;
}

//output
void outputRational(Rational x) {
    printf("%d/%u\n", x.numerator, x.denominator);
}

Rational addRational(Rational x, Rational y) {
    Rational z;
    x.numerator = x.numerator * y.denominator + y.numerator * x.denominator;
    z.denominator = x.denominator * y.denominator;
    return z;
}

Rational multRational(Rational x, Rational y) {
    //TODO:
    return x;
}

bool cmpRational(Rational x, Rational y) {
    return(x.numerator * y.denominator > y.denominator * x.denominator);
}

unsigned gcd(unsigned x, unsigned y) {
    //TODO
    return 0;
}

void reduceRational(Rational* x) {
    unsigned d = gcd(x->numerator, x->denominator);
    x->numerator /= d;
    x->denominator /= d;
}



