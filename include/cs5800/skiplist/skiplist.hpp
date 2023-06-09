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
    Node *search(int key);
    void print();
    ~SkipList();
protected:
    Node *head, *tail;
    std::random_device rd;
    std::mt19937 gen;
    std::bernoulli_distribution d;
    virtual int get_rand_bit();
};
