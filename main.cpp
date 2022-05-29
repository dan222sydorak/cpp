#include <iostream>

int check_nulls(int num) {
    int nulls = 0;
    while(num > 0) {
        if(num % 2 == 0) nulls++;
        num = num >> 1;
    }

    return nulls;
}

int check_ones(int num) {
    int nulls = 0;
    while(num > 0) {
        if(num % 2 == 1) nulls++;
        num = num >> 1;
    }

    return nulls;
}

bool same_bits(int num1, int num2) {
    int tmp = num1 & num2;
    return check_ones(tmp) > 0;
}


int main() {
    int num1, num2;
    std::cout << "Enter num1 & num2: ";
    std::cin >> num1 >> num2;

    std::cout << check_nulls(num1) << " " << check_nulls(num2) << std::endl;
    std::cout << same_bits(num1, num2);

    return 0;
}
