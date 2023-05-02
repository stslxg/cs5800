#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "hash/hash.hpp"

constexpr int M = 1000;

Hash hash_table(M);

void parse() {
    char c;
    std::string word;
    int total = 0;
    while ((c = getchar()) != EOF) {
        if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
            c = tolower(c);
            word += c;
        } else if (word.size() > 0) {
            hash_table.insert(word, 1);
            total++;
            word = "";
        }
    }
    std::cout << "wc: " << total << std::endl;
} 

void print_all() {
    for (auto [w, c]: hash_table.list()) {
        std::cout << w << " " << c << std::endl;
    }
}

void print_hist() {
    std::map<int, int> res = hash_table.hist();
    std::cout << "len: count" << std::endl;
    int total = 0;
    for (auto [k, v]: res) {
        std::cout << k << ": " << v << std::endl;
        total += k * v;
    }
    std::cout << "unique wc: " << total << std::endl;
}

int main() {
    parse();
    print_hist();
    //print_all();
    return 0;
}

