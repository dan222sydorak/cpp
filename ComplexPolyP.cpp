/* File ComplexPolyP.cpp
 * Realization of ComplexPolyP class and functions for it
 * Done by !!!!!!!!!!!!!!! (group !!!)
 * Date 25.05.2022
 * Implementation of ComplexPolyP and additional functions
 */

#include <ctime>
#include <iomanip>
#include "ComplexPolyP.h"

// Fast Fourier Transform
ComplexPolyP ComplexPolyP::fft() const {
    int n = this->size();

    // checking if size is power of 2
    if(std::pow(2, std::log2(n)) != n) {
        throw std::logic_error("Can`t do fft, because the size isn`t power of 2");
    }

    // returning because 1th root of 1 is 1 => f(x0) = a0 * x0 = a0 * 1 = a0
    if(n == 1) return *this;

    // finding all the Nth roots of 1
    std::vector<ComplexP> roots(n);
    for (int i = 0; i < n; i++) {
        double alpha = 2 * M_PI * i / n;
        roots[i] = ComplexP{cos(alpha), sin(alpha)};
    }

    // counting our subpolynomials A(x) and B(x)
    ComplexPolyP A(n/2), B(n/2);
    for(int i = 0; i < n/2; i++) {
        A[i] = this->at(2*i);
        B[i] = this->at(2*i+1);
    }

    // finding their values in omega_0, omega_2, omega_4 ...
    A = A.fft();
    B = B.fft();

    // finally, using our formula f(xi) = A(xi^2) + omega_i*B(xi^2)
    ComplexPolyP res(n);
    for(int i = 0; i < n; i++) {
        res[i] = round(A[i % (n / 2)] + roots[i] * B[i % (n / 2)], 5);
    }

    return res;
}

// Inverse Fast Fourier Transform
ComplexPolyP ComplexPolyP::inverse_fft() const {
    // counting coefficient for matrix with negative omegas
    // (omega_0, omega_-1, ...)
    ComplexPolyP tmp = this->fft();

    // as omega_k = omega_(k+N)%N = omega_k+N
    // reversing negative omegas, so omega_-1 = omega_(-1+N) = omega_(N-1)
    std::reverse(tmp.begin() + 1, tmp.end());

    // as bi = ai * N received from fft, we will find ai = bi / N
    for(int i = 0; i < tmp.size(); i++) {
        tmp[i] = round(tmp[i] / ComplexP{tmp.size()}, 3);
    }

    // clearing redundant coefficients
    tmp.fit();
    return tmp;
}

// polynomial reciprocal
ComplexPolyP ComplexPolyP::recip() const {
    int n = this->size();

    //  checking necessary requirements
    // size is power of 2, highest-level coefficient isn`t 0
    if(this->at(n - 1) == 0 || std::pow(2, std::log2(n)) != n) {
        throw std::logic_error("Can`t do recip with such poly");
    }

    ComplexPolyP res(*this);

    //if n=1 then f^-1*f=1 -> a0 * f^-1 = 1 -> f^-1 = 1/a0
    if(n == 1) {
        res[0] = round(ComplexP{1} / res[0], 5);
        return res;
    }

    // Rev(f) mod x^(n/2)
    std::reverse(res.begin(), res.end());
    res.resize(n / 2);
    std::reverse(res.begin(), res.end());
    // going into recursion
    ComplexPolyP q = res.recip();

    // 2q and resizing to fit q^2*Rev(f) because we read coef backwards
    res = (q * 2).scale(3 * n / 2 - 2);
    // 2q - q^2*Rev(f) mod x^(N-1)
    res = (res - q * q * (*this)).scale(-n + 2);

    return res;
}

// multiplying by x^t_size
ComplexPolyP ComplexPolyP::scale(const int &t_size) const {
    ComplexPolyP res(*this);
    for(int i = 0; i < std::fabs(t_size); i++) {
        if(t_size >= 0) {
            // multiplying x^t_size
            // adding new levels of ComplexPolyP
            res.m_coefficients.insert(
                    res.m_coefficients.begin(), ComplexP{0});
            res.resize(res.size()+1);
        } else {
            // dividing x^(abs(t_size))
            // erasing redundant levels of ComplexPolyP
            res.m_coefficients.erase(res.m_coefficients.begin());
            res.resize(res.size()-1);
        }
    }
    return res;
}

// evaluate value in specified point x
ComplexP ComplexPolyP::value(const ComplexP &x) const {
    ComplexP res{0, 0};
    for(int i = 0; i < this->size(); i++) {
        res = res + m_coefficients[i] * (x^i);
    }

    return res;
}

// evaluating derivative
ComplexPolyP ComplexPolyP::derivative() const {
    if(m_size <= 1) return ComplexPolyP(1);

    ComplexPolyP res(m_size-1);

    for(int i = 1; i < this->size(); i++) {
        res[i-1] = ComplexP{i} * m_coefficients[i];
    }

    return res;
}

// finding the nearest root to point x
ComplexP ComplexPolyP::root_Newton(const ComplexP &x) const {
    const double eps = 1e-10;
    ComplexP ans = x, x_0;

    do {
        x_0 = ans;
        ans = x_0 - this->value(x_0)/this->derivative().value(x_0);
    } while(std::fabs(ans.Re - x_0.Re) >= eps);

    return ans;
}

// formatted output to file
void ComplexPolyP::fprint(const std::string &file_name, const int &column, const int &precision) {
    std::ofstream ofstream(file_name, std::ios::binary);
    if(ofstream.is_open()) {
        if(column > 0) {
            for(int i = 0; i < this->size(); i++) {
                ofstream << round(this->at(i), precision);
                if((i+1) % column != 0)
                    ofstream << ' ';
                if(i != this->size()-1 && (i+1) % column == 0)
                    ofstream << std::endl;
            }
        } else {
            ofstream << *this;
        }
        ofstream.close();
    } else std::cout << "Unable to open the file. Make sure it exists.";
}

// console output for ComplexPolyP
std::ostream& operator<<(std::ostream &ostream, const ComplexPolyP &poly) {
    bool flag = false;
    for(int i = 0; i < poly.size(); i++) {
        if(poly.at(i) == ComplexP{0}) continue;
        if(flag) ostream << " + ";
        if(poly.at(i) != ComplexP{1} || i == 0) {
            flag = true;
            if(poly.at(i).Im != 0 && i != 0) {
                ostream << '(' << poly.at(i) << ')';
            } else {
                ostream << poly.at(i);
            }
            if(i != 0) ostream << " * ";
        }
        if(i != 0) {
            flag = true;
            ostream << "x";
            if(i != 1) ostream << '^' << i;
        }
    }

    if(!flag) {
        ostream << 0;
    }
    return ostream;
}

// console input for ComplexPolyP
std::istream& operator>>(std::istream &istream, ComplexPolyP &poly) {
    std::string str;
    getline(istream, str);
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    std::string tmp;
    int pos = 1, end_pos;
    bool is_neg;
    for(int i = 0; i < poly.size(); i++) {
        end_pos = str.find(")", pos);
        tmp = str.substr(pos, end_pos - pos);
        if(i != poly.size()-1){
            pos = str.find("(", end_pos) + 1;
            is_neg = (std::find(str.begin() + end_pos, str.begin() + pos, '+') - str.begin()) < 0;
        } else {
            is_neg = (std::find(str.begin() + end_pos, str.end(), '+') - str.begin()) < 0;
        }
        if(is_neg)
            poly[i] = -stoc(tmp);
        else
            poly[i] = stoc(tmp);

        if(pos == 0) break;
    }

    return istream;
}

// string input
ComplexPolyP inputc_CP(const std::string &str) {
    ComplexPolyP tmp;
    std::stringstream ss;
    ss << str;
    ss >> tmp;
    return tmp;
}

// generation function
ComplexPolyP generate(const size_t &size, const double &lower_bound, const double &upper_bound) {
    srand(time(NULL));

    ComplexPolyP res(size);
    ComplexP tmp;
    for(int i = 0; i < size; i++) {
        tmp.Re = lower_bound + (upper_bound - lower_bound) * (double)rand() / RAND_MAX;
        tmp.Im = lower_bound + (upper_bound - lower_bound) * (double)rand() / RAND_MAX;
        res[i] = tmp;
    }

    return res;
}