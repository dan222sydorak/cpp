#include <iostream>
#include <fstream>

int main() {
    std::ifstream ifstream;
    ifstream.open("test.txt");

    double nums[1000];
    double avg = 0;
    int i = 0;
    for(; i < 1000 && ifstream >> nums[i]; i++) {
        avg += nums[i];
    }
    ifstream.close();
    avg /= i;

    int amount = 0;
    for(int j = 0; j < i; j++) {
        if(nums[j] < avg) amount++;
    }

    std::cout << amount;

    return 0;
}
