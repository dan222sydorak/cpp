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

double* Gauss(double ** &matrix, int n, int m, double* x) {
    double **tmp = copy(matrix, n, m);
    double *tmp_x = new double[m];
    for(int i = 0; i < m; i++) {
        tmp_x[i] = x[i];
    }

    bool vectors[m];

    double *swap;
    double swap_x;
    for(int i = 0; i < m; i++) {
        if(tmp[i][i] != 0) continue;

        for(int j = 0; j < m; j++) {
            if(tmp[j][i] != 0 && !vectors[j]) {
                vectors[j] = true;
                swap = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = swap;

                swap_x = tmp_x[i];
                tmp_x[i] = tmp_x[j];
                tmp_x[j] = swap_x;
            }
        }

        if(tmp[i][i] == 0) throw std::runtime_error("Can`t do Gauss");
    }

    double coef = 0;
    for(int i = 0; i < std::min(n, m); i++) {
        for(int j = i+1; j < m; j++) {
            coef = tmp[j][i] / tmp[i][i];
            for(int k = 0; k < n; k++) {
                tmp[j][k] -= coef*tmp[i][k];
                if(fabs(tmp[j][k]) < 1e-5) {
                    tmp[j][k] = 0;
                }
            }
            tmp_x[j] -= coef*tmp_x[i];
        }
    }
//    std::cout << std::endl;
//    output_matrix(tmp, n, m);

    for(int i = std::min(n, m)-1; i >= 0; i--) {
        for(int j = i-1; j >= 0; j--) {
            coef = tmp[j][i] / tmp[i][i];
            for(int k = 0; k < n; k++) {
                tmp[j][k] -= coef*tmp[i][k];
                if(fabs(tmp[j][k]) < 1e-5) {
                    tmp[j][k] = 0;
                }
            }
            tmp_x[j] -= coef*tmp_x[i];
        }
    }

//    std::cout << std::endl;
//    output_matrix(tmp, n, m);
//    std::cout << std::endl;
//    for(int i = 0; i < n; i++) {
//        std::cout << tmp_x[i] << " ";
//    }
//    std::cout << std::endl;

    double *ans = new double[m];
    for(int i = 0; i < m; i++) {
        ans[i] = tmp_x[i]/tmp[i][i];
        if(fabs(ans[i]) < 1e-5) {
            ans[i] = 0;
        }
    }
    free(tmp);

    return ans;
}

double** inverse_matrix(double **&matrix, int n) {
    double **tmp = copy(matrix, n, n);

    double *x = new double[n];
    for(int i = 0; i < n; i++) x[i] = 0;

    double *ans;
    for(int i = 0; i < n; i++) {
        if(i != 0) x[i-1] = 0;
        x[i] = 1;
        ans = Gauss(matrix, n, n, x);
        for(int j = 0; j < n; j++) {
            tmp[j][i] = ans[j];
        }
    }

    return tmp;
}

void free(double** matrix, double m) {
    for(int i = 0; i < m; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

int main() {
    int n = 3;

    double **res = input_matrix(n, n, false);

    double **tmp;

    tmp = inverse_matrix(res, n);
    output_matrix(tmp, n, n);

    free(res, n);
    free(tmp, n);
    return 0;
}
