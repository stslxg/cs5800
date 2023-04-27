#include <iostream>
#include <vector>
#include <limits.h>
#include <random>

using namespace std;

constexpr float prob = 0.5;

struct Node {
    int val;
    vector<Node*> next;
};

class SL {
public:
    SL(): gen(rd()), d(prob) {
        head = new Node;
        head->val = INT_MIN;
        tail = new Node;
        tail->val = INT_MAX;
        head->next.push_back(tail);
        tail->next.push_back(nullptr);
    }

    void insert(int key) {
        vector<Node*> res = __search(key);
        if (res[0]->next[0]->val == key)
            return;
        int i = 0;
        Node *p = new Node;
        p->val = key;
        do {
            p->next.push_back(res[i]->next[i]);
            res[i]->next[i] = p;
            if (d(gen)) {
                i++;
                if (i >= head->next.size()) {
                    head->next.push_back(tail);
                    tail->next.push_back(nullptr);
                    res.push_back(head);
                }
            } else {
                break;
            }
        } while (true);
    }

    bool del(int key) {
        vector<Node*> res = __search(key);
        if (res[0]->next[0]->val != key)
            return false;
        else {
            Node *p = res[0]->next[0];
            for (int i = 0; i < res.size(); i++)
                if (res[i]->next[i] == p)
                    res[i]->next[i] = p->next[i];
                else
                    break;
            delete p;
            return true;
        }
    }

    bool lookup(int key) {
        vector<Node*> res = __search(key);
        if (res[0]->next[0]->val == key)
            return true;
        else
            return false;
    }

    void print() {
        for (int i = 0; i < head->next.size(); i++) {
            cout << head->val;
            Node *p = head->next[i];
            while (p) {
                cout << " -> " << p->val;
                p = p->next[i];
            }
            cout << endl;
        }
    }
private:
    Node *head, *tail;
    int size;
    random_device rd;
    mt19937 gen;
    bernoulli_distribution d;
    vector<Node*> __search(int key) {
        vector<Node*> prevs(head->next.size(), nullptr);
        Node *p = head;
        for (int i = head->next.size() - 1; i >= 0; i--) {
            while (p->next[i] && p->next[i]->val < key) {
                p = p->next[i];
            }
            prevs[i] = p;
        }
        return prevs;
    }
};

int main() {
    SL L;
    while (true) {
        char c;
        int k;
        cin >> c;
        if (c == 'i') {
            cin >> k;
            L.insert(k);
        } else if (c == 'l') {
            cin >> k;
            cout << L.lookup(k) << endl;
        } else if (c == 'p') {
            L.print();
        } else if (c == 'd') {
            cin >> k;
            cout << L.del(k) << endl;
        }
    }
    return 0;
}

