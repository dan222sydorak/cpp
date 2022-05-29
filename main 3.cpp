#include <iostream>
#include <cmath>
#include <ctime>

const double lower_bound = -100;
const double upper_bound = 100;

double** input_matrix(int n, int m, bool is_random) {
    srand(time(NULL));
    double **res = new double*[m];
    for(int i = 0; i < m; i++) {
        res[i] = new double[n];
        for(int j = 0; j < n; j++) {
            if(is_random) {
                res[i][j] = lower_bound + (upper_bound-lower_bound)*((double)rand()/RAND_MAX);
            } else {
                std::cout << "Enter coef (" << i << "," << j << "): ";
                std::cin >> res[i][j];
            }
        }
    }

    return res;
}

void output_matrix(double** matrix, int n, int m) {
    for(int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

double** copy(double **matrix, int n, int m) {
    double **res = new double*[m];
    for(int i = 0; i < m; i++) {
        res[i] = new double[n];
        for(int j = 0; j < n; j++) {
            res[i][j] = matrix[i][j];
        }
    }

    return res;
}

void remove_odd_rows(double** &matrix, int &m) {
    double **tmp = new double*[(m+1)/2];

    for(int i = 0; i < m; i++) {
        if(i % 2 == 0) {
            tmp[i/2] = matrix[i];
        } else {
            delete[] matrix[i];
        }
    }
    matrix = tmp;
    m = (m+1)/2;
}

void free(double** matrix, double n, double m) {
    for(int i = 0; i < m; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

int main() {
    int n = 3, m = 5;

    double **res = input_matrix(n, m, true);

    output_matrix(res, n, m);
    std::cout << std::endl;

    remove_odd_rows(res, m);

    output_matrix(res, n, m);

    free(res, n, m);
    return 0;
}
