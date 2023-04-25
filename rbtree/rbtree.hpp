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
    void left_rotate(Node *x);
    void right_rotate(Node *y);
    void transplant(Node *u, Node *v);
    void insert_fixup(Node *z);
};

static void __sort(Node *r);
static Node* __min(Node *r);
static Node* __max(Node *r);
static Node* __search(Node *r, int key);
static int __get_depth(Node *r);