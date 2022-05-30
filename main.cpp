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
    double **res = new double *[m];
    for (int i = 0; i < m; i++) {
        res[i] = new double[n];
        for (int j = 0; j < n; j++) {
            res[i][j] = matrix[i][j];
        }
    }

    return res;
}

void swap_vertical_matrix(double **&matrix, int n) {
    double tmp;

    for(int i = 0; i < n/2; i++) {
        for(int j = 0; j < n; j++) {
            tmp = matrix[j][i];
            matrix[j][i] = matrix[j][n-1-i];
            matrix[j][n-1-i] = tmp;
        }
    }
}

void free(double** matrix, double m) {
    for(int i = 0; i < m; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

int main() {
    int n = 5;

    double **res = input_matrix(n, n, true);

    output_matrix(res, n, n);
    std::cout << std::endl;

    swap_vertical_matrix(res, n);

    output_matrix(res, n, n);

    free(res, n);

    return 0;
}
