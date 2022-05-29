#include <iostream>

int main() {
    std::string input;
    std::cout << "Enter string: ";
    getline(std::cin, input);

    std::string out;
    for(int i = 0; i < input.size(); i++) {
        while(std::isspace(input[i])) {
            i++;
        }
        if(!out.empty() && std::isspace(input[i-1])) {
            out.append(1, ',');
        }
        if(i != input.size()) out.append(1, input[i]);
    }
    out.append(1, '.');

    std::cout << out;
    return 0;
}
