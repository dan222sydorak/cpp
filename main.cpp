#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>
#include <iomanip>

int main() {
    std::ifstream ifstream;
    ifstream.open("test.txt");
    if(!ifstream) return 0;

    double num = 0;
    bool is_neg = false;
    std::stringstream ss;
    std::string numstr;
    for(std::string line; getline(ifstream, line); ) {
        for(int i = 0; i < line.size(); i++) {
            if(is_neg) is_neg = false;
            if(line[i] == '-') {
                is_neg = true;
                if(i != line.size()-1) i++;
            }
            if(std::isdigit(line[i])) {
                numstr.clear();
                do {
                    numstr += line[i];
                    if(i == line.size()-1) break;
                    i++;
                } while(std::isdigit(line[i]) || line[i] == '.');
                if(i != line.size()-1) i--;
                if(is_neg) numstr = "-" + numstr;
                num = std::stod(numstr);
                if(num > 0) {
                    ss << std::setprecision(10) << log(num);
                } else {
                    ss << std::setprecision(7) << exp(num);
                }
            }
            ss << line[i];
        }
        ss << '\n';
    }
    ifstream.close();

    std::ofstream ofstream;
    ofstream.open("test.txt");
    std::string res = ss.str();
    ofstream << res;
    ofstream.close();
    return 0;
}
