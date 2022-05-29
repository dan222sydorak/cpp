#include <iostream>
#include <fstream>
#include <string>

struct Toy {
    std::string title;
    double price;
    int min_age, max_age;
};

void write(std::ofstream &ofstream, const Toy &toy) {
    unsigned int stringLength = toy.title.length();
    ofstream.write((char*)( &stringLength ), sizeof( stringLength ));
    ofstream.write(toy.title.c_str(), toy.title.length() );
    ofstream.write((char*) &toy.price, sizeof(double));
    ofstream.write((char*) &toy.min_age, sizeof(int));
    ofstream.write((char*) &toy.max_age, sizeof(int));
}

void read(std::ifstream &ifstream, Toy &toy) {
    unsigned int stringLength;
    ifstream.read( (char*)( &stringLength ), sizeof( stringLength ) );
    toy.title.resize( stringLength );
    ifstream.read((char *) toy.title.c_str(), stringLength);
    ifstream.read((char*) &toy.price, sizeof(double));
    ifstream.read((char*) &toy.min_age, sizeof(int));
    ifstream.read((char*) &toy.max_age, sizeof(int));
}

std::ostream& operator<<(std::ostream &ostream, const Toy &toy) {
    ostream << "Title: " << toy.title << std::endl;
    ostream << "Price: " << toy.price << std::endl;
    ostream << "Age: from " << toy.min_age << " to " << toy.max_age << std::endl;

    return ostream;
}

int main() {
    std::ifstream ifstream;
    Toy toys[5];
//    toys[0] = {"Constructor", 23.43, 2, 5};
//    toys[1] = {"Barby", 100.23, 7, 15};
//    toys[2] = {"Car", 54.2, 10, 18};
//    toys[3] = {"Car", 100, 6, 18};
//    toys[4] = {"Bicycle", 600, 5, 12};
    ifstream.open("test.dat", std::ios::binary);
    for(int i = 0; i < 5; i++) {
        read(ifstream, toys[i]);
    }

    double price;
    std::cout << "Enter price: ";
    std::cin >> price;

    for(int i = 0; i < 5; i++) {
        if(toys[i].price < price && toys[i].min_age <= 5 && toys[i].max_age >= 5) std::cout << toys[i];
    }
    return 0;
}
