#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>

using namespace std;
constexpr int M = 300;

struct Node {
    string word;
    int count;
    Node *prev, *next;
};

class Hash {
public:
    void insert(string word, int count) {
        int i = __hash(word);
        Node *p = __search(word);
        if (p) {
            p->count += count;
        } else {
            p = new Node;
            p->word = word;
            p->count = count;
            p->next = H[i];
            if (H[i])
                H[i]->prev = p;
            p->prev = nullptr;
            H[i] = p;
        }
    }

    void del(string word) {
        int i = __hash(word);
        Node *p = __search(word);
        if (p) {
            if (p->next)
                p->next->prev = p->prev;
            if (p->prev)
                p->prev->next = p->next;
            else
                H[i] = p->next;
            delete p;
        }
    }

    void increase(string word) {
        Node *p = __search(word);
        if (p)
            (p->count)++;
        else
            insert(word, 1);
    }

    int find(string word) {
        Node *p = __search(word);
        if (p)
            return p->count;
        else
            return 0;
    }

    map<int, int> hist() {
        map<int, int> res;
        for (int i = 0; i < M; i++) {
            Node *p = H[i];
            int len = 0;
            while (p) {
                len++;
                p = p->next;
            }
            res[len]++;
        }
        return res;
    }

    vector<string> list_all_keys() {
        vector<string> res;
        for (int i = 0; i < M; i++) {
            Node *p = H[i];
            while (p) {
                res.push_back(p->word);
                p = p->next;
            }
        }
        return res;
    }

    vector<pair<string,int>> list() {
        vector<pair<string,int>> res;
        for (int i = 0; i < M; i++) {
            Node *p = H[i];
            while (p) {
                res.emplace_back(p->word, p->count);
                p = p->next;
            }
        }
        return res;
    }
private:
    Node *H[M];
    int __hash(string word) {
        unsigned long v = 5381;
        for (char c: word) {
            v = v * 33 + c;
        }
        return v % M;
    }
    Node* __search(string word) {
        int i = __hash(word);
        Node *p = H[i];
        while (p) {
            if (p->word == word)
                return p;
            p = p->next;
        }
        return nullptr;
    }
};

Hash hash_table;

void parse() {
    char c;
    string word;
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
    cout << "wc: " << total << endl;
} 

void print_all() {
    for (auto [w, c]: hash_table.list()) {
        cout << w << " " << c << endl;
    }
}

void print_hist() {
    map<int, int> res = hash_table.hist();
    cout << "len: count" << endl;
    int total = 0;
    for (auto [k, v]: res) {
        cout << k << ": " << v << endl;
        total += k * v;
    }
    cout << "unique wc: " << total << endl;
}

int main() {
    parse();
    print_hist();
    //print_all();
    return 0;
}

