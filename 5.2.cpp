#include <iostream>
using namespace std;
//a
int main() {
    int n, t1 = 0, t2 = 1, nextTerm = 0;

    cout << "n: ";
    cin >> n;

    cout << "F=: ";

    for (int i = 1; i <= n; ++i) {
        if (i == 1) {
            cout << t1 << ", ";
            continue;
        }
        if (i == 2) {
            cout << t2 << ", ";
            continue;
        }
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;

        cout << nextTerm << ", ";
    }
    return 0;
}

//b
#include <iostream>
using namespace std;

int main() {
    int t1 = 0, t2 = 1, nextTerm = 0, n;

    cout << "n: ";
    cin >> n;
    cout << "F=: " << t1 << ", " << t2 << ", ";

    nextTerm = t1 + t2;

    while (nextTerm <= n) {
        cout << nextTerm << ", ";
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
    }
    return 0;
}
//г)
#include <stdio.h>
#include <iostream>

int main() {
    int last = 0, next = 1;
    long sum = 1;

    for (; next < 1000; next += last) {
        last = next - last;
        sum += next;
    }
    std::cout << sum;
    return 0;
}