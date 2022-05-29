#include <iostream>

typedef struct {
    std::string cypher;
    std::string title;
    std::string author;
} Book;

typedef struct {
    int num_ticket;
    std::string surname;
} Reader;

typedef struct {
    Book book;
    Reader reader;
    std::string date;
} Record;

std::ostream& operator<<(std::ostream &ostream, const Reader &reader) {
    std::cout << "Reader: " << std::endl;
    std::cout << "Ticket number: " << reader.num_ticket << std::endl;
    std::cout << "Surname: " << reader.surname << std::endl;

    return ostream;
}

std::istream& operator>>(std::istream &istream, Reader &reader) {
    std::cout << "Enter reader`s ticket number: ";
    istream >> reader.num_ticket;
    std::cout << "Enter reader`s surname: ";
    istream >> reader.surname;

    return istream;
}

std::ostream& operator<<(std::ostream &ostream, const Book &b) {
    std::cout << "Book: " << std::endl;
    std::cout << "Title: " << b.title << std::endl;
    std::cout << "Author: " << b.author << std::endl;
    std::cout << "Cypher: " << b.cypher << std::endl;

    return ostream;
}

std::istream& operator>>(std::istream &istream, Book &b) {
    std::cout << "Enter book`s title: ";
    istream >> b.title;
    std::cout << "Enter book`s author: ";
    istream >> b.author;
    std::cout << "Enter book`s cypher: ";
    istream >> b.cypher;

    return istream;
}

std::ostream& operator<<(std::ostream &ostream, const Record &r) {
    ostream << "Record" << std::endl;
    ostream << "Date: " << r.date << std::endl;
    ostream << r.book;
    ostream << r.reader;
    ostream << std::endl;

    return ostream;
}

std::istream& operator>>(std::istream &istream, Record &r) {
    std::cout << "Enter record`s date: ";
    istream >> r.date;
    std::cout << "Enter book: " << std::endl;
    istream >> r.book;
    std::cout << "Enter reader: " << std::endl;
    istream >> r.reader;

    return istream;
}

int main() {
    Record r;
    std::cin >> r;
    std::cout << r;

    return 0;
}
