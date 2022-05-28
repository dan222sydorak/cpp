#include <iostream>

template<typename T>
auto sum(T* arr, size_t n) {
    if constexpr(std::is_pointer<T>::value) {
        T res;
        typedef typename std::remove_pointer<T>::type A;
        res = new A[n];
        for(int i = 0; i < n; i++) {
            res[i] = *arr[i];
        }
        return res;
    } else if constexpr(std::is_same<T, char>::value) {
        std::string tmp;
        for(int i = 0; i < n; i++) {
            tmp += arr[i];
        }
        return tmp;
    } else {
        T res;
        if constexpr(!std::is_same<T, std::string>::value) res = 0;
        for(int i = 0; i < n; i++) {
            res += arr[i];
        }
        return res;
    }
}

int main() {
    int size = 3;
    int v1[] = {1, 2, 3};
    double v2[] = {1.0, 2.0, 3.0};
    std::string v3[] = {"ab", "cd", "ef"};
    char v4[] = {'a', 'b', 'c'};

    int v5_1[] = {1, 4};
    int v5_2[] = {2};
    int v5_3[] = {3};
    int* v5[] = {v5_1, v5_2, v5_3};

    std::cout << sum(v1, size) << std::endl;
    std::cout << sum(v2, size) << std::endl;
    std::cout << sum(v3, size) << std::endl;
    std::cout << sum(v4, size) << std::endl;

    int *tmp = sum(v5,size);
    for(int i = 0; i < size; i++) {
        std::cout << tmp[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
