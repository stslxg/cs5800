#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "hash/hash.hpp"

void Hash::insert(const std::string& word, int count) {
    int i = hash(word);
    Node *p = search(word);
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

void Hash::del(const std::string& word) {
    int i = hash(word);
    Node *p = search(word);
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

void Hash::increase(const std::string& word) {
    Node *p = search(word);
    if (p)
        (p->count)++;
    else
        insert(word, 1);
}

int Hash::find(const std::string& word) const {
    Node *p = search(word);
    if (p)
        return p->count;
    else
        return 0;
}

std::map<int, int> Hash::hist() const {
    std::map<int, int> res;
    for (int i = 0; i < m; i++) {
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

std::vector<std::string> Hash::list_all_keys() const {
    std::vector<std::string> res;
    for (int i = 0; i < m; i++) {
        Node *p = H[i];
        while (p) {
            res.push_back(p->word);
            p = p->next;
        }
    }
    return res;
}

std::vector<std::pair<std::string, int>> Hash::list() const {
    std::vector<std::pair<std::string, int>> res;
    for (int i = 0; i < m; i++) {
        Node *p = H[i];
        while (p) {
            res.emplace_back(p->word, p->count);
            p = p->next;
        }
    }
    return res;
}

int Hash::hash(const std::string& word) const {
    unsigned long v = 5381;
    for (char c: word) {
        v = v * 33 + c;
    }
    return v % m;
}

Node* Hash::search(const std::string& word) const {
    int i = hash(word);
    Node *p = H[i];
    while (p) {
        if (p->word == word)
            return p;
        p = p->next;
    }
    return nullptr;
}

Hash::~Hash() {
    for (int i = 0; i < m; i++) {
        Node *p = H[i];
        while (p) {
            Node *q = p;
            p = p->next;
            delete q;
        }
    }
}
