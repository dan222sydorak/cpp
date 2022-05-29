#include <iostream>
#include <fstream>
#include <regex>

int main() {
    std::ifstream istream;
    istream.open("test.txt");

    char c;
    std::cout << "Input the start character: ";
    std::cin >> c;

    std::string exp = "\\b" + std::string(1, char(std::tolower(c))) + "[a-zA-Z]*";

    std::regex regexp(exp);

    std::smatch m;

    std::stringstream ss;
    for(std::string line; getline(istream, line);) {
        std::for_each(line.begin(), line.end(), [](char & c) {
            c = std::tolower(c);
        });

        while (std::regex_search (line, m, regexp)) {
            for (auto x:m) ss << x << " ";
            line = m.suffix().str();
        }
        ss << std::endl;
    }
    istream.close();

    std::ofstream ofstream;
    ofstream.open("output.txt");
    ofstream << ss.str();
    ofstream.close();

    return 0;
}
