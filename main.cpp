#include <iostream>

int min_arr(int* arr, int N) {
    int min_el = arr[0];
    for(int i = 0; i < N; i+=2) {
        if(arr[i] < min_el) {
            min_el = arr[i];
        }
    }
    return min_el;
}

int full_sq(int* arr, int N) {
    int amount = 0;
    for(int i = 0; i < N/2; i++) {
        if(arr[i] == arr[N-1-i]) amount++;
    }
    return amount;
}

int main() {
    int N;
    std::cout << "Enter N: ";
    std::cin >> N;

    int arr[N];
    for(int i = 0; i < N; i++) {
        std::cin >> arr[i];
    }

    std::cout << min_arr(arr, N) << std::endl;
    std::cout << full_sq(arr, N) << std::endl;
    return 0;
}
