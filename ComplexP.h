#ifndef COMPLEXPOLY_CPP_COMPLEXP_H
#define COMPLEXPOLY_CPP_COMPLEXP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

class ComplexP {
public:
    double Re, Im; ///< real and imaginary parts of number

    /* ComplexP constructor
     *
     * @param - IN real value (default = 0)
     * @param - IN imaginary value (default = 0)
     */
    ComplexP(const double &t_re = 0, const double &t_im = 0)
    : Re(t_re), Im(t_im) { }

    /* overloaded equal operator
     *
     * compare ComplexP by its Re and Im parts at the same time
     *
     * @param - IN ComplexP to be compared
     * @result - true if equal, false otherwise
     */
    bool operator==(const ComplexP &rhs) const {
        return Re == rhs.Re && Im == rhs.Im;
    }

    /* overloaded unequal operator
     *
     * opposite to equal
     *
     * @param - IN ComplexP to be compared
     * @result - true if unequal, false otherwise
     */
    bool operator!=(const ComplexP &rhs) const {
        return !(*this == rhs);
    }

    /* overloaded unary minus sign operation
     *
     * changes all the parts into opposite by the sign
     *
     * @result - new ComplexP that is operation result
     */
    ComplexP operator-() const {
        return {-Re, -Im};
    }

    /* overloaded xor operation
     *
     * it is not xor anymore
     * now it means ComplexP num to the specific power
     *
     * @param - power
     * @result - new ComplexP that is operation result
     */
    ComplexP operator^(const int &rhs) const {
        ComplexP res{1, 0};
        for(int i = 0; i < std::fabs(rhs); i++) {
            res = res * *this;
        }
        if(rhs < 0) {
            res = ComplexP{1} / res;
        }
        return res;
    }

    /* overloaded adding operation
     *
     * summing appropriate parts of ComplexP numbers
     *
     * @param - IN ComplexP to added
     * @result - new ComplexP that is operation result
     */
    ComplexP operator+(const ComplexP &rhs) const {
        return {Re + rhs.Re, Im + rhs.Im};
    }

    /* overloaded subtracting operation
     *
     * subtracting appropriate parts of ComplexP numbers
     *
     * @param - IN ComplexP to be subtracted by
     * @result - new ComplexP that is operation result
     */
    ComplexP operator-(const ComplexP &rhs) const {
        return {Re - rhs.Re, Im - rhs.Im};
    }

    /* overloaded multiplying operation
     *
     * multiplying ComplexP numbers, the idea:
     * (a+bi)*(c+di) = ac + adi + bci + bd * i^2 =
     * = (ac - bd) + (ad + bc)i
     *
     * @param - IN ComplexP to be multiplied by
     * @result - new ComplexP that is operation result
     */
    ComplexP operator*(const ComplexP &rhs) const {
        return {Re * rhs.Re - Im * rhs.Im, Re * rhs.Im + Im * rhs.Re};
    }

    /* overloaded dividing operation
     *
     * dividing ComplexP numbers with idea:
     * (a+bi)/(c+di) = (a+bi)(c-di)/(c+di)(c-di) =
     * = (ac - adi + bci - bd * i^2)/(c^2 - d^2 * i^2) =
     * = (ac+bd + (bc-ad)i)/(c^2 + d^2)
     *
     * @param - IN ComplexP to be divided by
     * @result - new ComplexP that is operation result
     */
    ComplexP operator/(const ComplexP &rhs) const {
        if(rhs.Re == 0 && rhs.Im == 0) throw std::runtime_error("Division by zero");

        double divisor = rhs.Re * rhs.Re + rhs.Im * rhs.Im;
        return {(Re * rhs.Re + Im * rhs.Im) / divisor,
                (Im * rhs.Re - Re * rhs.Im) / divisor};
    }
};

/* overloaded output operator
 *
 * write formatted ComplexP into output stream
 *
 * @param - IN ostream to write the ComplexP
 * @param - IN ComplexP to be written
 * @result - ostream with written poly
 */
std::ostream& operator<<(std::ostream &ostream, const ComplexP &num);

/* overloaded input operator
 *
 * read input stream
 *
 * @param - IN istream to read a ComplexP
 * @param - IN ComplexP
 * @result - istream without ComplexP, that was read
 */
std::istream& operator>>(std::istream &istream, ComplexP &num);

/* string to ComplexP operation
 *
 * convert string to ComplexP
 *
 * @param - IN string to be converted
 * @result - new ComplexP if string was convertable
 */
ComplexP stoc(const std::string &str);

/* ComplexP to string operation
 *
 * convert ComplexP to string
 *
 * @param - IN ComplexP to be converted
 * @result - string with ComplexP output
 */
std::string ctos(const ComplexP &num);

/* rounding ComplexP
 *
 * rounds ComplexP number with some precision
 *
 * @param - IN ComplexP to be rounded
 * @param - IN precision of rounding (1e(precision), default = 0)
 * @result - new ComplexP that is operation result
 */
ComplexP round(const ComplexP &num, const int &precision = 0);

#endif //COMPLEXPOLY_CPP_COMPLEXP_H
