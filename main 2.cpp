#include <iostream>

typedef struct {
    bool is_man;
    double height;
} Human;

double avg_women(Human *arr, int size) {
    double sum = 0;
    int amount = 0;
    for(int i = 0; i < size; i++) {
        if(!arr[i].is_man) {
            sum += arr[i].height;
            amount++;
        }
    }
    return (amount > 0 ? sum / amount : 0);
}

double heighest_man(Human *arr, int size) {
    double max_height = 0;
    for(int i = 0; i < size; i++) {
        if(arr[i].is_man && max_height < arr[i].height) {
            max_height = arr[i].height;
        }
    }
    return max_height;
}

bool same_height(Human *arr, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < i; j++) {
            if(arr[i].height == arr[j].height) return true;
        }
    }

    return false;
}


int main() {
    Human arr[5];
    arr[0] = {true, 1.6};
    arr[1] = {false, 1.56};
    arr[2] = {true, 1.56};
    arr[3] = {false, 1.78};
    arr[4] = {true, 1.75};

    std::cout << avg_women(arr, 5) << std::endl;
    std::cout << heighest_man(arr, 5) << std::endl;
    std::cout << same_height(arr, 5) << std::endl;
    return 0;
}
