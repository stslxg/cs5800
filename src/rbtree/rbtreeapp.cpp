#include <iostream>
#include "rbtree.hpp"

int main() {
    Tree t;
    t.insert(7);
    t.insert(4);
    t.insert(2);
    t.sort();
    t.insert(5);
    t.sort();
    t.insert(6);
    t.sort();
    t.insert(1);
    t.sort();
    t.insert(3);
    t.sort();
    t.del(t.search(4));
    t.sort();
    std::cout << t.pred(t.search(5))->val << std::endl;
    std::cout << t.suc(t.search(3))->val << std::endl;
    return 0;
}