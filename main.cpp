#include <iostream>
#include <fstream>

class Book {
public:
    Book() = default;

    Book(const std::string &title_, const std::string &author_, const int &pages_, const int &date_) :
    title(title_), author(author_), pages(pages_), date(date_) { }

    std::string get_title() { return title; }
    std::string get_author() { return author; }
    int get_pages() { return pages; }
    int get_date() { return date; }

    void read_str(const std::string &str) {
        char buff1[50], buff2[50];
        sscanf(str.c_str(), "%s ;%s ;%i;%i", buff1, buff2, &pages,&date);
        title = std::string(buff1);
        author = std::string(buff2);
    }

    friend std::ostream& operator<<(std::ostream &ostream, const Book &book);

private:
    std::string title, author;
    int pages, date;
};

std::ostream& operator<<(std::ostream &ostream, const Book &book) {
    ostream << "Title: " << book.title << std::endl;
    ostream << "Author: " << book.author << std::endl;
    ostream << "Pages: " << book.pages << std::endl;
    ostream << "Date: " << book.date << std::endl;

    return ostream;
}


int main() {
    Book book[100];
    std::ifstream ifstream;
    ifstream.open("test.txt");
    if(!ifstream) return 0;

    int size = 0;
    for (std::string line; std::getline(ifstream, line); size++)
    {
        book[size].read_str(line);
    }

    while(true) {
        std::string cmd;
        bool author = false, title = false;
        std::cout << "Enter what to find (author/title) (or smth else to exit): ";
        std::cin >> cmd;
        if(cmd == "author") author = true;
        else if(cmd == "title") title = true;
        else break;
        std::cout << "Enter str to find (or q to exit): ";
        std::cin >> cmd;

        if(cmd == "q") break;

        for(int i = 0; i < size; i++) {
            if(author && book[i].get_author().find(cmd) != std::string::npos ||
               title && book[i].get_title().find(cmd) != std::string::npos ) {
                std::cout << "Book #" << i << std::endl;
                std::cout << book[i];
            }
        }
    }

    return 0;
}
