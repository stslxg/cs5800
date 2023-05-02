#pragma once
#include <unordered_map>
#include <utility>

class Node {
public:
    Node(int key): parent(nullptr), child(nullptr), sibling(nullptr), key(key), degree(0) {}; 
    Node *parent, *child, *sibling;
    int key, degree;
};

class BiHeap {
public:
    Node *head;
    BiHeap(): head(nullptr) {};
    BiHeap(int key);
    void insert(int key);
    int min();
    void merge(BiHeap& h);
    int extract_min();
    bool decrease(int key, int new_key);
    bool del(int key);
    void print();
    ~BiHeap();
private:
    std::unordered_map<int, Node*> pos;
};
