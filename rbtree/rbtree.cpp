#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    bool red;
    Node *left, *right, *parent;
    int val;
    Node(bool c, Node *l, Node *r, Node *p, int v): red(c), left(l), right(r), parent(p), val(v) {};
    Node(): Node(true, nullptr, nullptr, nullptr, 0) {};
};
void __sort(Node *r) {
    if (!r) return;
    cout << "( ";
    __sort(r->left);
    cout << r->val << ": ";
    if (r->red)
        cout << "r ";
    else
        cout << "b ";
    __sort(r->right);
    cout << " )";
}

void sort(Node *r) {
    __sort(r);
    cout << endl;
}
    
Node* min(Node *r) {
    if (r->left) {
        return min(r->left);
    } else {
        return r;
    }
}

Node* max(Node *r) {
    if (r->right) {
        return max(r->right);
    } else {
        return r;
    }
}

Node* search(Node *r, int key) {
    if (!r || r->val == key)
        return r;
    if (r->val > key) {
        return search(r->left, key);
    } else {
        return search(r->right, key);
    }
}

Node* suc(Node *r) {
    if (r->right)
        return min(r->right);
    Node *y = r->parent;
    while (y && r == y->right) {
        r = y;
        y = y->parent;
    }
    return y;
}

Node* pred(Node *r) {
    if (r->left)
        return max(r->left);
    Node *y = r->parent;
    while (y && r == y->left) {
        r = y;
        y = y->parent;
    }
    return y;
}

void left_rotate(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

void right_rotate(Node **root, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right)
        x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) {
        *root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    
    x->right = y;
    y->parent = x;
}

int get_depth(Node *r) {
    if (!r)
        return 0;
    return 1 + max(get_depth(r->left), get_depth(r->right));
}


void transplant(Node **root, Node *u, Node *v) {
    if (!u->parent) {
        *root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v)
        v->parent = u->parent;
}

void del(Node **root, Node* z) {
    if (!z->left) {
        transplant(root, z, z->right);
    } else if (!z->right) {
        transplant(root, z, z->left);
    } else {
        Node *y = min(z->right);
        if (y->parent != z) {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    cout << "d: " << get_depth(*root) << endl;
}


void insert_fixup(Node **root, Node *z) {
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
                    left_rotate(root, z);
                }
                z->parent->red = false;
                z->parent->parent->red = true;
                right_rotate(root, z->parent->parent);
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
                    right_rotate(root, z);
                }
                z->parent->red = false;
                z->parent->parent->red = true;
                left_rotate(root, z->parent->parent);
            }
        } 
    }
    (*root)->red = false;
}




void insert(Node **root, int key) {
    Node *y = nullptr;
    Node *x = *root;
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
        *root = z;
    } else if (key < y->val) {
        y->left = z;
    } else {
        y->right = z;
    }
    insert_fixup(root, z);
    cout << "d: " << get_depth(*root) << endl;
}

int main()
{
    Node *r = nullptr;
    insert(&r, 7);
    insert(&r, 4);
    insert(&r, 2);
    sort(r);
    insert(&r, 5);
    sort(r);
    insert(&r, 6);
    sort(r);
    insert(&r, 1);
    sort(r);
    insert(&r, 3);
    sort(r);
    del(&r, search(r, 4));
    sort(r);
    cout << pred(search(r, 5))->val << endl;
    cout << suc(search(r, 3))->val << endl;
    return 0;
}
