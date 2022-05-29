#include <iostream>
#include <cmath>

double** input_matrix(int n, int m) {
    double **res = new double*[m];
    for(int i = 0; i < m; i++) {
        res[i] = new double[n];
        for(int j = 0; j < n; j++) {
            std::cout << "Enter coef (" << i << "," << j << "): ";
            std::cin >> res[i][j];
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

double rank(double **matrix, int n, int m) {
    double **tmp = copy(matrix, n, m);

    bool vectors[m];

    double *swap;
    for(int i = 0; i < m; i++) {
        if(tmp[i][i] != 0) continue;

        for(int j = 0; j < m; j++) {
            if(tmp[j][i] != 0 && !vectors[j]) {
                vectors[j] = true;
                swap = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = swap;
            }
        }
    }

    double coef = 0;
    for(int i = 0; i < std::min(n, m); i++) {
        if(tmp[i][i] == 0) continue;
        for(int j = i+1; j < m; j++) {
            coef = tmp[j][i] / tmp[i][i];
            for(int k = 0; k < n; k++) {
                tmp[j][k] -= coef*tmp[i][k];
                if(fabs(tmp[j][k]) < 1e-5) {
                    tmp[j][k] = 0;
                }
            }
        }
    }
//    std::cout << std::endl;
//    output_matrix(tmp, n, m);

    for(int i = std::min(n, m)-1; i >= 0; i--) {
        if(tmp[i][i] == 0) continue;
        for(int j = i-1; j >= 0; j--) {
            coef = tmp[j][j+1] / tmp[i][i];
            for(int k = 0; k < n; k++) {
                tmp[j][k] -= coef*tmp[i][k];
                if(fabs(tmp[j][k]) < 1e-5) {
                    tmp[j][k] = 0;
                }
            }
        }
    }

//    std::cout << std::endl;
//    output_matrix(tmp, n, m);

    int rank = 0;
    bool is_non_zero_vector;
    for(int i = 0; i < m; i++) {
        is_non_zero_vector = false;
        for(int j = 0; j < n; j++) {
            if(tmp[i][j] != 0) {
                is_non_zero_vector = true;
                break;
            }
        }
        if(is_non_zero_vector) rank++;
    }

    free(tmp);

    return std::min(n, rank);
}

void free(double** matrix, double n, double m) {
    for(int i = 0; i < m; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

int main() {
    int n = 3, m = 4;

    double **res = input_matrix(n, m);

    output_matrix(res, n, m);

    std::cout << rank(res, n, m) << std::endl;

    free(res, n, m);
    return 0;
}
