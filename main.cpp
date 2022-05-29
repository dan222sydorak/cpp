#include <iostream>
#include <fstream>


void add_poly(const std::string &file_name) {
    std::ofstream ofstream;
    ofstream.open(file_name, std::ios_base::app);
    if(!ofstream) return;

    int m;
    std::cout << "Enter num of monomes: ";
    std::cin >> m;
    ofstream << m << " ";

    std::cout << "Enter pairs like (coef,deg): " << std::endl;
    std::string tmp;
    for(int i = 0; i < m; i++) {
        std::cin >> tmp;
        ofstream << tmp << " ";
    }
    ofstream << std::endl;
    ofstream.close();
}

int main() {
    add_poly("test.txt");
    return 0;
}
