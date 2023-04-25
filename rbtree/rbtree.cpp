#include <iostream>
#include <algorithm>
#include "rbtree.hpp"

static void __sort(Node *r);
static Node* __min(Node *r);
static Node* __max(Node *r);
static Node* __search(Node *r, int key);
static int __get_depth(Node *r);

void Tree::sort() {
    __sort(root);
    std::cout << std::endl;
}

Node* Tree::min() {
    return __min(root);
}

Node* Tree::max() {
    return __max(root);
}

Node* Tree::search(int key) {
    return __search(root, key);
}

Node* Tree::suc(Node *r) {
    if (r->right)
        return __min(r->right);
    Node *y = r->parent;
    while (y && r == y->right) {
        r = y;
        y = y->parent;
    }
    return y;
}

Node* Tree::pred(Node *r) {
    if (r->left)
        return __max(r->left);
    Node *y = r->parent;
    while (y && r == y->left) {
        r = y;
        y = y->parent;
    }
    return y;
}

void Tree::left_rotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void Tree::right_rotate(Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right)
        x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) {
        root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}

int Tree::get_depth() {
    return __get_depth(root);
}

void Tree::transplant(Node *u, Node *v) {
    if (!u->parent) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v)
        v->parent = u->parent;
}

void Tree::del(Node *z) {
    if (!z->left) {
        transplant(z, z->right);
    } else if (!z->right) {
        transplant(z, z->left);
    } else {
        Node *y = __min(z->right);
        if (y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    std::cout << "d: " << get_depth() << std::endl;
}

void Tree::insert_fixup(Node *z) {
    while (z->parent && z->parent->red) {
        if (z->parent->parent && z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y && y->red) {
                z->parent->red = false;
                y->red = false;
                z->parent->parent->red = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->red = false;
                z->parent->parent->red = true;
                right_rotate(z->parent->parent);
            }
        } else if (z->parent->parent && z->parent == z->parent->parent->right) {
            Node *y = z->parent->parent->left;
            if (y && y->red) {
                z->parent->red = false;
                y->red = false;
                z->parent->parent->red = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->red = false;
                z->parent->parent->red = true;
                left_rotate(z->parent->parent);
            }
        }
    }
    root->red = false;
}

void Tree::insert(int key) {
    Node *y = nullptr;
    Node *x = root;
    while (x) {
        y = x;
        if (key < x->val)
            x = x->left;
        else
            x = x->right;
    }

    Node *z = new Node();
    z->parent = y;
    z->val = key;
    if (!y) {
        root = z;
    } else if (key < y->val) {
        y->left = z;
    } else {
        y->right = z;
    }
    insert_fixup(z);
    std::cout << "d: " << get_depth() << std::endl;
}

void __sort(Node *r) {
    if (!r)
        return;
    std::cout << "( ";
    __sort(r->left);
    std::cout << r->val << ": ";
    if (r->red)
        std::cout << "r ";
    else
        std::cout << "b ";
    __sort(r->right);
    std::cout << " )";
}

Node* __min(Node *r) {
    if (r->left) {
        return __min(r->left);
    } else {
        return r;
    }
}

Node* __max(Node *r) {
    if (r->right) {
        return __max(r->right);
    } else {
        return r;
    }
}

Node* __search(Node *r, int key) {
    if (!r || r->val == key)
        return r;
    if (r->val > key) {
        return __search(r->left, key);
    } else {
        return __search(r->right, key);
    }
}

int __get_depth(Node *r)
{
    if (!r)
        return 0;
    return 1 + std::max(__get_depth(r->left), __get_depth(r->right));
}