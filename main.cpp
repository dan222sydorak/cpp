#include <iostream>
#include <list>

void showList(std::list<int> l)
{
    std::list<int>::iterator it;
    for (it = l.begin(); it != l.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}


int main() {
    int N;
    std::cout << "Enter N: ";
    std::cin >> N;

    std::list<int> l;
    int tmp;
    for(int i = 0; i < N; i++) {
        std::cin >> tmp;
        l.push_back(tmp);
    }
    if(N % 2 != 0) {
        l.push_back(0);
        N++;
    }
    showList(l);

    std::list<int> l2;
    for(int i = 0; i < N/2; i++) {
        l2.push_back(l.front());
        l.pop_front();
        l2.push_back(l.back());
        l.pop_back();
    }
    l = l2;
    showList(l);

    return 0;
}
