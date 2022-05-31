/* File ComplexPolyP.h
 * Realization of ComplexPolyP class and functions for it
 * Done by !!!!!!!!!!!!!!! (group !!!)
 * Date 25.05.2022
 *
 * Headers for ComplexPolyP
 */

#ifndef COMPLEXPOLY_CPP_COMPLEXPOLYP_H
#define COMPLEXPOLY_CPP_COMPLEXPOLYP_H

#include <vector>
#include <cmath>
#include "ComplexP.h"

/**
 * Implementation of a polynomial with complex coefficients
 */
class ComplexPolyP {
public:
    /* ComplexPolyP constructor
     *
     * @param - IN size of new ComplexPolyP (default = 1)
     */
    ComplexPolyP(const size_t &t_size = 1)
    : m_size(t_size) {
        m_coefficients.resize(t_size);
    }

    /* ComplexPolyP constructor
     *
     * @param - IN ComplexPolyP to be copied
     *
     * @overload
     */
    ComplexPolyP(const ComplexPolyP &copy) {
        m_coefficients = copy.m_coefficients;
        m_size = copy.m_size;
    }

    /* getter for ComplexPolyP size
     *
     * @result - size of ComplexPolyP
     */
    size_t size() const {
        return m_size;
    }

    /* resizing ComplexPolyP
     *
     * @param - IN new size for ComplexPolyP
     * @result - void
     */
    void resize(const size_t &t_size) {
        if(t_size < 0) throw std::logic_error("Can`t resize with negative size");
        m_coefficients.resize(t_size);
        m_size = t_size;
    }

    /* fitting function
     *
     * delete redundant high-level coefficients
     *
     * @result - void
     */
    void fit() {
        int i = this->size()-1;
        for(; i >= 0; i--) {
            if(this->at(i) != ComplexP{0, 0}) break;
        }
        this->resize(i+1);
    }

    /* getter for beginning of ComplexPolyP
     *
     * @result - iterator, that points to beginning
     */
    std::vector<ComplexP>::iterator begin() {
        return m_coefficients.begin();
    }

    /* getter for end of ComplexPolyP
     *
     * @result - iterator, that points to the memory element
     *           next to end of ComplexPolyP
     */
    std::vector<ComplexP>::iterator end() {
        return m_coefficients.end();
    }

    /* overloaded access operator
     *
     * gives access to i coefficient
     *
     * @param - IN i
     * @result - reference to i coefficient (mutable)
     */
    ComplexP& operator[](const int &index) {
        if(index < 0 || index >= m_size) throw std::out_of_range("Index is out of range");
        return m_coefficients[index];
    }

    /* getter for i coefficient
     *
     * analog of access operator, but immutable
     *
     * @param - IN i
     * @result - value of i coefficient
     */
    ComplexP at(const int &index) const {
        if(index < 0 || index >= m_size) throw std::out_of_range("Index is out of range");
        return m_coefficients[index];
    }

    /* overloaded equal operator
     *
     * compare ComplexPolyP by its coefficients
     *
     * @param - IN ComplexPolyP to be compared
     * @result - true if equal, false otherwise
     */
    bool operator==(const ComplexPolyP &poly) const {
        if(this->size() != poly.size()) return false;
        for(int i = 0; i < this->size(); i++) {
            if(this->at(i) != poly.at(i)) return false;
        }
        return true;
    }

    /* overloaded unequal operator
     *
     * opposite to equal
     *
     * @param - IN ComplexPolyP to be compared
     * @result - true if unequal, false otherwise
     */
    bool operator!=(const ComplexPolyP &poly) const {
        return !(*this == poly);
    }

    /* overloaded adding
     *
     * @param - IN ComplexPolyP to be added
     * @result - new ComplexPolyP that contains operation result
     */
    ComplexPolyP operator+(const ComplexPolyP &poly) const {
        size_t max_size = std::max(this->size(), poly.size());
        ComplexPolyP res(max_size);

        for(int i = 0; i < max_size; i++) {
            if(this->size() <= i) {
                res[i] = poly.at(i);
            } else if(poly.size() <= i) {
                res[i] = m_coefficients[i];
            } else res[i] = m_coefficients[i] + poly.at(i);
        }

        return res;
    }

    /* overloaded unary minus operator
     *
     * changes all the coefficients signs to opposite
     *
     * @result - new ComplexPolyP that contains operation result
     */
    ComplexPolyP operator-() const {
        ComplexPolyP res(*this);

        for(int i = 0; i < this->size(); i++) {
            res[i] = -res[i];
        }

        return res;
    }

    /* overloaded subtracting
     *
     * @param - IN ComplexPolyP to be subtracted
     * @result - new ComplexPolyP that contains operation result
     */
    ComplexPolyP operator-(const ComplexPolyP &poly) const {
        return *this + -poly;
    }

    /* Fast Fourier Transform
     *
     * algorithm to get all the f(xi) as the new ComplexPolyP
     * where xi - primitive Nth root of 1, N - ComplexPolyP size
     *                                         and also power of 2
     * it is optimized with idea that f(x) = A(x^2) + x*B(x^2), where
     * A(x) - polynomial with all even f coefficients
     * B(x) has all odd f coefficients
     * Using the Nth roots of 1 and knowing that
     * (omega_k)^2=omega_k*omega_k=omega_(2k%N)
     * make our formula twice that effective,
     * because now we have the same answer for
     * A((omega_(N/2 + k))^2) = A(omega_(N+2k)%N) = A(omega_2k) if k < N/2
     *
     * @result - ComplexPolyP with f(xi) as its coefficients
     */
    ComplexPolyP fft() const;

    /* Inverse Fast Fourier Transform
     *
     * algorithm to get all the ComplexPolyP coefficients
     * for ComplexPolyP that contains all f(xi) received with fft
     *
     * @result - ComplexPolyP with relative coefficients
     */
    ComplexPolyP inverse_fft() const;

    /* overloaded scalar multiplying
     *
     * @param - IN scalar num
     * @result - new ComplexPolyP that contains operation result
     */
    ComplexPolyP operator*(const double &num) const {
        ComplexPolyP res(*this);
        for (int i = 0; i < res.size(); i++) res[i] = ComplexP{num} * res[i];
        return res;
    }

    /* overloaded polynomial multiplying
     *
     * uses FFT that makes it works about O(n*logn)
     * the main idea is that
     * FFT(A*B) = FFT(C)
     * FFT(C) = FFT(A)*FFT(B)
     * C = INV_FFT(FFT(F)*FFT(B))
     *
     * @param - IN ComplexPolyP to be multiplied
     * @result - new ComplexPolyP that contains operation result
     */
    ComplexPolyP operator*(const ComplexPolyP &poly) const {
        // resizing polynomials to be the power of 2 and
        //                         >= resulting polynomial size
        // (needed by FFT algorithm)
        int max_size = this->size() * poly.size();
        max_size = (int)std::pow(2, std::ceil(std::log2(max_size)));
        ComplexPolyP tmp1 = *this, tmp2 = poly;
        tmp1.resize(max_size); tmp2.resize(max_size);

        // FFT(A), FFT(B)
        tmp1 = tmp1.fft(); tmp2 = tmp2.fft();

        // FFT(A)*FFT(B)
        ComplexPolyP tmp3(tmp1.size());
        for(int i = 0; i < std::min(tmp1.size(), tmp2.size()); i++) tmp3[i] = tmp1[i] * tmp2[i];

        // INV_FFT(FFT(A)*FFT(B))
        return tmp3.inverse_fft();
    }

    /* Scaling ComplexPolyP
     *
     * multiplying ComplexPolyP by x^t_size
     * if t_size < 0, then we`ll discard all the coefficients ai: ai*x^i,
     * where i < 0 after multiplying
     *
     * @param - IN the x power
     * @result - new ComplexPolyP that contains operation result
     */
    ComplexPolyP scale(const int &t_size) const;

    /* polynomial reciprocal
     *
     * it is defined as: x^(2N-2) / f(x),
     * where N is power of 2
     *
     * @result - reciprocal of f(x)
     */
    ComplexPolyP recip() const;

    /* overloaded division operator
     *
     * uses idea that if we have reciprocal (s(x) = x^(2N-2) / g(x) -
     * we can evaluate it straight forward)
     * then we may change division with
     * f(x) / g(x) = f(x) * s(x) / x^(2N-2)
     *
     */
    ComplexPolyP operator/(const ComplexPolyP &poly) const {
        // m = deg(f(x))
        int m = this->size() - 1;
        // n = deg(g(x))
        int n = poly.size() - 1;

        // poly.size + nd = 2^k
        int nd = (int)std::pow(2, std::ceil(std::log2(n+1)) ) - 1 - n;
        ComplexPolyP tmp1 = this->scale(nd), tmp2 = poly.scale(nd);
        m += nd; n += nd;

        // s = x^(2N-2) / g(x)
        ComplexPolyP s = tmp2.recip();
        // res = f(x) * s / x^(2N-2)
        ComplexPolyP res = (tmp1 * s).scale(-2 * n);

        if(m > 2*n) {
            // tmp3 = x^(2N-1)
            ComplexPolyP tmp3(2*n+1);
            tmp3[tmp3.size()-1] = ComplexP{1};
            // t = x^(2N-1) - x^(2N-2) / g(x) * g(x) = x^(2N-1) - x^(2N-2)
            ComplexPolyP t = tmp3  - s * tmp2;
            // q2 = (f(x) * t / x^(2N-2)) / g(x)
            ComplexPolyP q2 = (tmp1 * t).scale(-2*n) / tmp2;
            res = res + q2;
        }

        return res;
    }

    /* overloaded reminder operator
     *
     * finding reminder from f(x) = h(x)*g(x) + r(x) => r(x) = f(x) - h(x)*g(x),
     * where h(x) - result of operation f(x)/g(x)
     *
     * @param - IN g(x)
     * @result - new ComplexPolyP that contains operation result
     */
    ComplexPolyP operator%(const ComplexPolyP &poly) const {
        ComplexPolyP tmp = *this / poly;
        tmp = tmp * poly;
        return *this - tmp;
    }

    /* evaluating ComplexPolyP value in specific point
     *
     * formula is f(xi) = a0 + a1 * xi + a2 * xi^2 + ...
     *
     * @param - IN specific point xi
     * @result - f(xi)
     */
    ComplexP value(const ComplexP &x) const;

    /* polynomial derivative
     *
     * evaluate counting that rule: (x^i)' = i * x^(i-1)
     *
     * @result - polynomial derivative of first order
     */
    ComplexPolyP derivative() const;

    /* finding the nearest polynomial root to point x
     *
     * uses Newton recursion:
     * x_n = x_(n-1) - f(x_(n-1)) / f'(x_(n-1))
     * until precision 1e-5 is reached
     * precision counted as abs(x_n - x_(n-1))
     *
     * @params - IN specific point x
     * @result - polynomial root near x with 1e-5 precision
     */
    ComplexP root_Newton(const ComplexP &x) const;

    /* output into file
     *
     * managed output
     * you can specify columns count and coefficients precision
     *
     * @param - IN file name
     * @param - IN columns count for coefficients
     * @param - IN coefficients precision
     * @result - void
     */
    void fprint(const std::string &file_name, const int &column = 0, const int &precision = 3);

private:
    size_t m_size; ///< stands for polynomial size
    std::vector<ComplexP> m_coefficients; ///< all the polynomial coefficients
};

/* functions for ComplexPolyP */

/* overloaded output operator
 *
 * write formatted polynomial into output stream
 *
 * @param - IN ostream to write the poly
 * @param - IN ComplexPolyP to be written
 * @result - ostream with written poly
 */
std::ostream& operator<<(std::ostream &ostream, const ComplexPolyP &poly);

/* overloaded input operator
 *
 * read input stream
 *
 * @param - IN istream to read a poly
 * @param - IN ComplexPolyP
 * @result - istream without poly, that was read
 */
std::istream& operator>>(std::istream &istream, ComplexPolyP &poly);

/* input from string
 *
 * string processing to ComplexPolyP
 *
 * @param - IN string with supposed ComplexPolyP
 * @result - ComplexPolyP that was read
 */
ComplexPolyP inputc_CP(const std::string &str);

/* generator ComplexPolyP
 *
 * create new ComplexPolyP with random coefficients specified with parameters
 *
 * @param - IN size of new ComplexPolyP
 * @params - IN lower and upper bounds of coefficients generating
 *           (applied for real and imaginary parts of number separately)
 * @result - generated ComplexPolyP
 */
ComplexPolyP generate(const size_t &size, const double &lower_bound = -100, const double &upper_bound = 100);
#endif //COMPLEXPOLY_CPP_COMPLEXPOLYP_H