#include <iostream>
#include <cmath>

double f(const double &x) {
    return std::tan(x) - x;
}

int main() {
    double left = 1e-3, right = 1.5;

    double eps;
    std::cout << "Enter eps: ";
    std::cin >> eps;

    double x;
    do {
        x = (left + right)/2;
        if(f(left) > f(x)) {
            left = x;
        } else {
            right = x;
        }
    } while(std::fabs(f(x)) >= eps);

    std::cout << x;

    return 0;
}
