#pragma once

class Node {
public:
    bool red;
    Node *left, *right, *parent;
    int val;
    Node(bool c, Node *l, Node *r, Node *p, int v): red(c), left(l), right(r), parent(p), val(v) {};
    Node(): Node(true, nullptr, nullptr, nullptr, 0) {};
};

class Tree {
public:
    Tree(): root(nullptr) {};
    void sort();
    Node* min();
    Node* max();
    Node* search(int key);
    Node* suc(Node *r);
    Node* pred(Node *r);
    int get_depth();
    void del(Node *z);
    void insert(int key);
private:
    Node* root;
    virtual void left_rotate(Node *x);
    virtual void right_rotate(Node *y);
    void transplant(Node *u, Node *v);
    void insert_fixup(Node *z);
};
