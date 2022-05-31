#include <cmath>
#include "ComplexP.h"

// console output for ComplexP
std::ostream& operator<<(std::ostream &ostream, const ComplexP &num) {
    ostream << num.Re;
    if(num.Im != 0) {
        if(num.Im == -1) ostream << '-';
        else if(num.Im > 0) {
            ostream << '+';
            if(num.Im != 1) {
                ostream << num.Im;
            }
        } else ostream << num.Im;

        ostream << 'i';
    }

    return ostream;
}

// console input for ComplexP
std::istream& operator>>(std::istream &istream, ComplexP &num) {
    std::string str;
    getline(istream, str);
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    int split_pos = str.find('+');
    if(split_pos < 0){
        split_pos = str.find('-', 1);
    }
    if(str[split_pos+1] == '-') str.erase(std::remove(str.begin(), str.end(), '+'), str.end());

    num.Re = std::stod(str.substr(0, split_pos));
    if(str[split_pos+1] == 'i') num.Im = -1;
    else num.Im = std::stod(str.substr(split_pos, str.find('i')));

    return istream;
}

// string to complex function
ComplexP stoc(const std::string &str) {
    ComplexP tmp;
    std::stringstream ss;
    ss << str;
    ss >> tmp;
    return tmp;
}

// ComplexP to string function
std::string ctos(const ComplexP &num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

// rounding real and imaginary parts of number
ComplexP round(const ComplexP &num, const int &precision)  {
    if(precision < 0) throw std::logic_error("precision must be positive");

    int dec = (int)std::round(std::pow(10.0, (double)precision));

    double n_Re = std::round(num.Re * dec) / dec;
    double n_Im = std::round(num.Im * dec) / dec;
    return ComplexP{n_Re, n_Im};
}