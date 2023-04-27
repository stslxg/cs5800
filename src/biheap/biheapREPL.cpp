#include <iostream>
#include "biheap.hpp"

int main() {
    char c;
    int k;
    BiHeap H;
    while (true) {
        std::cin >> c;
        if (c == 'i') {
            std::cin >> k;
            H.insert(k);
        } else if (c == 'm') {
            std::cout << H.min() << std::endl;
        } else if (c == 'p') {
            H.print();
        } else if (c == 'e') {
            std::cout << H.extract_min() << std::endl;
        } else if (c == 'd') {
            std::cin >> k;
            int kk;
            std::cin >> kk;
            if (kk < k)
                std::cout << H.decrease(k, kk) << std::endl;
            else
                std::cout << false << std::endl;
        } else if (c == 'k') {
            std::cin >> k;
            std::cout << H.del(k) << std::endl;
        }
    }
    return 0;
}