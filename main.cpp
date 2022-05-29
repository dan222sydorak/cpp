#include <iostream>
#include <fstream>

int main() {
    std::ifstream ifstream;
    ifstream.open("test.txt");

    std::string res;
    int prev_num = -1, num;
    while(ifstream >> num) {
        if(prev_num == -1) {
            prev_num = num;
            continue;
        }

        if(prev_num > num) {
            res += std::to_string(prev_num*prev_num);
        } else {
            res += std::to_string(prev_num);
        }

        res += " ";
        prev_num = num;
    }
    res += std::to_string(num);

    std::ofstream ofstream;
    ofstream.open("test.txt");
    ofstream << res;
    ofstream.close();
    return 0;
}
