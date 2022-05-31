#include "ComplexPoly.h"

#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <io.h>
#include <time.h>

#define MAX_SIZE 1000

struct ComplexPoly {
    int m_size;
    Complex* m_coefficients[MAX_SIZE];
};

ComplexPoly* new_ComplexPoly(int t_size) {
    ComplexPoly *tmp = (ComplexPoly*) malloc(sizeof(ComplexPoly));
    tmp->m_size = 0;
    if(!resize_ComplexPoly(tmp, t_size)) return NULL;

    return tmp;
}

ComplexPoly* copy_ComplexPoly(ComplexPoly *copy) {
    ComplexPoly *tmp = new_ComplexPoly(size(copy));
    for(int i = 0; i < size(copy); i++) {
        tmp->m_coefficients[i] = copy->m_coefficients[i];
    }
    return tmp;
}

void free_ComplexPoly(ComplexPoly *poly) {
    for(int i = 0; i < size(poly); i++) {
        free(poly->m_coefficients[i]);
    }
    free(poly->m_coefficients);
}

int resize_ComplexPoly(ComplexPoly *poly, int t_size) {
    if(t_size > MAX_SIZE || t_size <= 0) return 0;
    for(int i = size(poly); i < t_size; i++) {
        poly->m_coefficients[i] = new_Complex(0, 0);
    }
    poly->m_size = t_size;
    return 1;
}

int size(ComplexPoly *poly) {
    return poly->m_size;
}

void fit(ComplexPoly *poly) {
    int i = poly->m_size-1;
    for(; i >= 0; i--) {
        if(!equal_Complex(poly->m_coefficients[i], new_Complex(0, 0))) break;
    }
    i++;
    resize_ComplexPoly(poly, i);
}

Complex* get_coefficient(ComplexPoly *poly, int pos) {
    if(pos < 0 || pos > poly->m_size) return NULL;

    return poly->m_coefficients[pos];
}

int set_coefficient(ComplexPoly *poly, int pos, Complex *num) {
    if(get_coefficient(poly, pos) == NULL) return 0;

    *get_coefficient(poly, pos) = *num;
    return 1;
}

int equal_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2) {
    if(poly1->m_size != poly2->m_size) return 0;

    for(int i = 0; i < poly1->m_size; i++) {
        if(!equal_Complex(poly1->m_coefficients[i], poly2->m_coefficients[i])) return 0;
    }

    return 1;
}

ComplexPoly* fft(ComplexPoly *poly) {
    int n = poly->m_size;

    if(pow(2, log2(n)) != n) return NULL;

    if(n == 1) return poly;

    Complex* roots[n];
    for (int i = 0; i < n; i++) {
        double alpha = 2 * M_PI * i / n;
        roots[i] = new_Complex(cos(alpha), sin(alpha));
    }

    ComplexPoly *A = new_ComplexPoly(n/2), *B = new_ComplexPoly(n/2);
    for(int i = 0; i < n/2; i++) {
        A->m_coefficients[i] = poly->m_coefficients[2*i];
        B->m_coefficients[i] = poly->m_coefficients[2*i+1];
    }

    A = fft(A);
    B = fft(B);

    ComplexPoly *res = new_ComplexPoly(n);
    Complex *tmp = new_Complex(0, 0);
    for(int i = 0; i < n; i++) {
        tmp = mul_Complex(roots[i], B->m_coefficients[i % (n / 2)]);
        res->m_coefficients[i] = round_Complex(plus_Complex(A->m_coefficients[i % (n / 2)], tmp), 5);
    }

    return res;
}

void swap(Complex *num1, Complex *num2) {
    Complex *tmp = num1;
    num1 = num2;
    num2 = tmp;
}

ComplexPoly* inverse_fft(ComplexPoly *poly) {
    ComplexPoly *tmp = fft(poly);

    Complex *ctmp;
    for(int i = 0; i < size(tmp); i++) {
        if(i != 0 && i <= size(tmp)/2) {
            ctmp = new_Complex(tmp->m_coefficients[i]->Re, tmp->m_coefficients[i]->Im);
            tmp->m_coefficients[i] = new_Complex(
                    tmp->m_coefficients[size(tmp)-i]->Re,
                    tmp->m_coefficients[size(tmp)-i]->Im
            );
            tmp->m_coefficients[size(tmp)-i] = ctmp;
        }
        tmp->m_coefficients[i] = round_Complex(
                div_Complex(tmp->m_coefficients[i], new_Complex(size(poly), 0) ),
                3);
    }

    fit(tmp);
    return tmp;
}

int insert_zero(ComplexPoly *poly) {
    if(poly->m_size >= MAX_SIZE) return 0;

    for(int i = poly->m_size; i > 0; i--) {
        poly->m_coefficients[i] = poly->m_coefficients[i-1];
    }
    poly->m_size++;
    poly->m_coefficients[0] = new_Complex(0, 0);

    return 1;
}

int erase_head(ComplexPoly *poly) {
    if(poly->m_size <= 1) return 0;

    for(int i = 0; i < poly->m_size-1; i++) {
        poly->m_coefficients[i] = poly->m_coefficients[i+1];
    }
    poly->m_size--;

    return 1;
}

ComplexPoly* scale(ComplexPoly *poly, int t_size) {
    ComplexPoly *res = copy_ComplexPoly(poly);
    for(int i = 0; i < abs(t_size); i++) {
        if(t_size >= 0) {
            insert_zero(res);
        } else {
            erase_head(res);
        }
    }
    return res;
}

void reverse(ComplexPoly *poly) {
    Complex *tmp;
    for(int i = 0; i < poly->m_size/2; i++) {
        tmp = poly->m_coefficients[i];
        poly->m_coefficients[i] = poly->m_coefficients[poly->m_size-1-i];
        poly->m_coefficients[poly->m_size-1-i] = tmp;
    }
}

ComplexPoly* recip(ComplexPoly *poly) {
    int n = size(poly);

    if(equal_Complex(poly->m_coefficients[n - 1], new_Complex(0, 0))
        || pow(2, log2(n)) != n) {
        return NULL;
    }

    ComplexPoly *res = copy_ComplexPoly(poly);

    if(n == 1) {
        res->m_coefficients[0] = round_Complex(
                div_Complex(new_Complex(1, 0), res->m_coefficients[0]),
                5);
        return res;
    }

    reverse(res);
    resize_ComplexPoly(res, n / 2);
    reverse(res);
    ComplexPoly *q = recip(res);
    if(q == NULL) return NULL;

    res = scalar_mul_ComplexPoly(q, 2);
    res = scale(res, 3 * n / 2 - 2);
    q = mul_ComplexPoly(q, q);
    res = minus_ComplexPoly(res, mul_ComplexPoly(q, poly));
    res = scale(res, -n + 2);

    return res;
}

ComplexPoly* neg_ComplexPoly(ComplexPoly *poly) {
    ComplexPoly *res = new_ComplexPoly(size(poly));
    for(int i = 0; i < size(poly); i++) {
        res->m_coefficients[i] = neg_Complex(poly->m_coefficients[i]);
    }
    return res;
}

ComplexPoly* plus_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2) {
    int max_size = fmax(size(poly1), size(poly2));
    ComplexPoly *res = new_ComplexPoly(max_size);

    for(int i = 0; i < max_size; i++) {
        if(size(poly1) <= i) {
            res->m_coefficients[i] = poly2->m_coefficients[i];
        } else if(size(poly2) <= i) {
            res->m_coefficients[i] = poly1->m_coefficients[i];
        } else res->m_coefficients[i] = plus_Complex(poly1->m_coefficients[i], poly2->m_coefficients[i]);
    }

    return res;
}



ComplexPoly* minus_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2) {
    return plus_ComplexPoly(poly1, neg_ComplexPoly(poly2));
}

ComplexPoly* scalar_mul_ComplexPoly(ComplexPoly *poly, double num) {
    ComplexPoly *res = new_ComplexPoly(size(poly));

    for (int i = 0; i < size(poly); i++) {
        res->m_coefficients[i] = mul_Complex(new_Complex(num, 0), poly->m_coefficients[i]);
    }

    return res;
}

ComplexPoly* mul_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2) {
    int max_size = size(poly1) * size(poly2);
    max_size = (int)pow(2, ceil(log2(max_size)));
    ComplexPoly *tmp1 = copy_ComplexPoly(poly1), *tmp2 = copy_ComplexPoly(poly2);
    resize_ComplexPoly(tmp1, max_size); resize_ComplexPoly(tmp2, max_size);

    tmp1 = fft(tmp1); tmp2 = fft(tmp2);

    ComplexPoly *tmp3 = new_ComplexPoly(size(tmp1));
    for(int i = 0; i < size(tmp1); i++) {
        tmp3->m_coefficients[i] = mul_Complex(tmp1->m_coefficients[i], tmp2->m_coefficients[i]);
    }

    return inverse_fft(tmp3);
}

ComplexPoly* div_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2) {
    int m = size(poly1) - 1;
    int n = size(poly2) - 1;

    int nd = (int)pow(2, ceil(log2(n+1)) ) - 1 - n;
    ComplexPoly *tmp1 = scale(poly1, nd), *tmp2 = scale(poly2, nd);
    m += nd; n += nd;

    ComplexPoly *s = recip(tmp2);
    ComplexPoly *res = mul_ComplexPoly(tmp1, s);
    res = scale(res, -2 * n);

    if(m > 2*n) {
        ComplexPoly *tmp3 = new_ComplexPoly(2*n+1);
        tmp3->m_coefficients[size(tmp3)-1] = new_Complex(1, 0);
        ComplexPoly *t = minus_ComplexPoly(tmp3, mul_ComplexPoly(s, tmp2));
        ComplexPoly *q2 = mul_ComplexPoly(tmp1, t);
        q2 = scale(q2,-2*n);
        q2 = div_ComplexPoly(q2, tmp2);
        res = plus_ComplexPoly(res, q2);
    }

    return res;
}

ComplexPoly* mod_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2) {
    ComplexPoly *tmp = div_ComplexPoly(poly1, poly2);
    tmp = mul_ComplexPoly(tmp, poly2);
    return minus_ComplexPoly(poly1, tmp);
}

Complex* value(ComplexPoly *poly, Complex *x) {
    Complex *res = new_Complex(0, 0);
    for(int i = 0; i < size(poly); i++) {
        res = plus_Complex(res, mul_Complex(poly->m_coefficients[i], power_Complex(x, i)));
    }

    return res;
}

ComplexPoly* derivative(ComplexPoly *poly) {
    if(size(poly) <= 1) return new_ComplexPoly(1);

    ComplexPoly *res = new_ComplexPoly(size(poly)-1);

    for(int i = 1; i < size(poly); i++) {
        res->m_coefficients[i-1] = mul_Complex(new_Complex(i, 0), poly->m_coefficients[i]);
    }

    return res;
}

Complex* root_Newton(ComplexPoly *poly, Complex *x) {
    const double eps = 1e-10;
    Complex *ans = new_Complex(x->Re, x->Im), *x_0 = new_Complex(0, 0);

    do {
        *x_0 = *ans;
        ans = minus_Complex(x_0, div_Complex( value(poly, x_0), value(derivative(poly), x_0)) );
    } while(fabs(ans->Re - x_0->Re) >= eps);

    return ans;
}

void fprint_ComplexPoly(ComplexPoly *poly, char *file_name, int column, int precision) {
    FILE *file;
    file = fopen(file_name, "w");

    if(column <= 0) {
        printf("Columns amount is wrong");
        return;
    }

    if(column > 0) {
        for(int i = 0; i < size(poly); i++) {
            fprintf(file, "%s", ctos(round_Complex(poly->m_coefficients[i], precision)));
            if((i+1) % column != 0)
                fprintf(file, " ");
            if(i != size(poly)-1 && (i+1) % column == 0)
                fprintf(file, "\n");
        }
    }

    fclose(file);
}

void print_ComplexPoly(ComplexPoly *poly) {
    int flag = 0;
    for(int i = 0; i < size(poly); i++) {
        if(equal_Complex(poly->m_coefficients[i], new_Complex(0, 0))) continue;
        if(flag) printf(" + ");
        if(!equal_Complex(poly->m_coefficients[i], new_Complex(1, 0)) || i == 0) {
            flag = 1;
            if(poly->m_coefficients[i]->Im != 0) {
                if(i != 0) printf("(");
                print_Complex(poly->m_coefficients[i]);
                if(i != 0) printf(")");
            } else {
                printf("%.3f", poly->m_coefficients[i]->Re);
            }
            if(i != 0) printf(" * ");
        }
        if(i != 0) {
            flag = 1;
            printf("x");
            if (i != 1) printf("^%i", i);
        }
    }

    if(!flag) {
        printf("0");
    }
}

void input_ComplexPoly(ComplexPoly *poly) {
    int buff_size = 1000;
    char *buff;
    buff = (char *)malloc(buff_size * sizeof(char));
    buff_size = getline(&buff, &buff_size, stdin);

    inputs_ComplexPoly(poly, buff, buff_size);
}

void inputs_ComplexPoly(ComplexPoly *poly, char *buff, int buff_size) {
    int cur_pos = 0, ord = 0;
    char numstr[buff_size], ordstr[buff_size];
    for(int i = 0; i < buff_size; i++) {
        if(buff[i] == ' ') continue;
        if(buff[i] == '\0') break;

        if(buff[i] == '(') {
            i++;
            cur_pos = i;
            for(; i < buff_size; i++) {
                if(buff[i] == ')') break;
                if(i == buff_size - 1) {
                    printf("Wrong format");
                    exit(0);
                }
                numstr[i - cur_pos] = buff[i];
            }
        }

        if(buff[i] == 'x') {
            i++;
            for(; i < buff_size; i++) {
                if(i == buff_size - 1) {
                    printf("Wrong format");
                    exit(0);
                }
                if(!isdigit(buff[i])) continue;

                cur_pos = i;
                while(isdigit(buff[i])) {
                    if(i == buff_size - 1) {
                        printf("Wrong format");
                        exit(0);
                    }
                    ordstr[i - cur_pos] = buff[i];
                    i++;
                }
                break;
            }

            ord = atoi(ordstr);
            *get_coefficient(poly, ord) = *stoc(numstr);
        }

        if(buff[i] == '+' && ord == 0) {
            *get_coefficient(poly, ord) = *stoc(numstr);
        }
    }
}


ComplexPoly* generate(int size, double lower_bound, double upper_bound) {
    srand(time(NULL));

    ComplexPoly *res = new_ComplexPoly(size);
    Complex *tmp = new_Complex(0, 0);
    for(int i = 0; i < size; i++) {
    tmp->Re = lower_bound + (upper_bound - lower_bound) * (double)rand() / RAND_MAX;
    tmp->Im = lower_bound + (upper_bound - lower_bound) * (double)rand() / RAND_MAX;
    res->m_coefficients[i] = tmp;
    }

    return res;
}