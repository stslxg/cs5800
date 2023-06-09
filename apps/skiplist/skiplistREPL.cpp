#include <iostream>
#include "skiplist/skiplist.hpp"

int main() {
    SkipList L;
    while (true) {
        char c;
        int k;
        std::cin >> c;
        if (c == 'i') {
            std::cin >> k;
            L.insert(k);
        } else if (c == 'l') {
            std::cin >> k;
            std::cout << std::boolalpha << L.lookup(k) << std::endl;
        } else if (c == 'p') {
            L.print();
        } else if (c == 'd') {
            std::cin >> k;
            std::cout << std::boolalpha << L.del(k) << std::endl;
        } else if (c == 'q') {
            break;
        }
    }
    return 0;
}
