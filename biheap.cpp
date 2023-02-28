#include <iostream>
#include <climits>
#include <utility>
#include <unordered_map>

using namespace std;

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
    BiHeap(int key) {
        Node *p = new Node(key);
        head = p;
    }
    
    void insert(int key) {
        if (!pos.count(key)) {
            BiHeap h(key);
            pos[key] = h.head;
            merge(h);
        }
    }
    
    int min() {
        auto [q, p] = __search_min();
        if (p)
            return p->key;
        else
            return INT_MAX;
    }
    
    void merge(BiHeap& h) {
        head = __merge(head, h.head);
        h.head = nullptr;
    }
    
    int extract_min() {
        auto [q, p] = __search_min();
        if (p) {
            int res = p->key;
            if (q)
                q->sibling = p->sibling;
            else
                head = p->sibling;
            p->sibling = nullptr;
            Node *reversed = nullptr;
            if (p->child) {
                reversed = __reverse(p->child);
            }
            head = __merge(head, reversed);
            pos.erase(res);
            delete p;
            return res;
        } else {
            return INT_MAX;
        }
    }
    
    bool decrease(int key, int new_key) {
        if (pos.count(key) && !pos.count(new_key)) {
            Node *p = pos[key];
            p->key = new_key;
            pos[new_key] = p;
            pos.erase(key);
            while (p->parent && p->parent->key > new_key) {
                p->key = p->parent->key;
                p->parent->key = new_key;
                pos[p->key] = p;
                pos[new_key] = p->parent;
                
                p = p->parent;
            }
            return true;
        } else {
            return false;
        }
    }
    
    bool del(int key) {
        if (pos.count(key)) {
            decrease(key, INT_MIN);
            extract_min();
            return true;
        } else {
            return false;
        }
    }
    
    void print() {
        __print(head);
    }
private:
    unordered_map<int, Node*> pos;
    Node* __reverse(Node *cur) {
        Node *prev = nullptr;
        while (cur) {
            Node *tmp = cur->sibling;
            cur->sibling = prev;
            cur->parent = nullptr;
            prev = cur;
            cur = tmp;
        }
        return prev;
    }
    
    void __print(Node *r) {
        while (r) {
            cout << "k: " << r->key << " d: " << r->degree;
            if (r->sibling)
                cout << " sib-k: " << r->sibling->key;
            cout << endl;
            __print(r->child);
            r = r->sibling;
        }    
    }
    pair<Node*, Node*> __search_min() {
        Node *q = nullptr, *p = head, *res_q = nullptr, *res_p = nullptr;
        int now = INT_MAX;
        while (p) {
            if (p->key < now) {
                res_q = q;
                res_p = p;
                now = p->key;
            }
            q = p;
            p = p->sibling;
        }
        
        return {res_q, res_p};
    }
    
    Node* __mergeTree(Node *p, Node *q) {
        if (p->key <= q->key) {
            q->sibling = p->child;
            p->child = q;
            q->parent = p;
            p->degree++;
            return p;
        } else {
            p->sibling = q->child;
            q->child = p;
            p->parent = q;
            q->degree++;
            return q;
        }
    }
    
    Node* __merge(Node *p, Node *q) {
        Node *cur = nullptr, *prev = nullptr, *head = nullptr, *next_p = nullptr, *next_q = nullptr;
        
        auto set_next = [&](Node *next_cur, bool advance_prev = true) {
            if (advance_prev)
                prev = cur;
            cur = next_cur;
            if (prev) {
                prev->sibling = cur;
            } else {
                head = cur;
            }
        };
        
        while (p || q) {
            if (p)
                next_p = p->sibling;
            if (q)
                next_q = q->sibling;
            
            if (p && q && p->degree == q->degree) {
                p->sibling = nullptr;
                q->sibling = nullptr;
                Node *mergered = __mergeTree(p, q);
                set_next(mergered);
                
                p = next_p;
                q = next_q;
            } else if (!q || (p && p->degree < q->degree)) {
                p->sibling = nullptr;
                if (cur && cur->degree == p->degree) {
                    Node *mergered = __mergeTree(cur, p);
                    set_next(mergered, false);
                } else {
                    set_next(p);
                }
                
                p = next_p;
            } else {
                q->sibling = nullptr;
                if (cur && cur->degree == q->degree) {
                    Node *mergered = __mergeTree(cur, q);
                    set_next(mergered, false);
                } else {
                    set_next(q);
                }
                
                q = next_q;
            }
        }
        
        return head;
    }
};


int main() {
    char c;
    int k;
    BiHeap H;
    while (true) {
        cin >> c;
        if (c == 'i') {
            cin >> k;
            H.insert(k);
        } else if (c == 'm') {
            cout << H.min() << endl;
        } else if (c == 'p') {
            H.print();
        } else if (c == 'e') {
            cout << H.extract_min() << endl;
        } else if (c == 'd') {
            cin >> k;
            int kk;
            cin >> kk;
            if (kk < k)
                cout << H.decrease(k, kk) << endl;
            else
                cout << false << endl;
        } else if (c == 'k') {
            cin >> k;
            cout << H.del(k) << endl;
        }
    }
    return 0;
}
