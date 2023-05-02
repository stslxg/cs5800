#pragma once
#include <vector>
#include <random>

struct Node {
    int val;
    std::vector<Node*> next;
};

class SkipList {
public:
    SkipList();
    void insert(int key);
    bool del(int key);
    bool lookup(int key);
    void print();
private:
    Node *head, *tail;
    int size;
    std::random_device rd;
    std::mt19937 gen;
    std::bernoulli_distribution d;
};
