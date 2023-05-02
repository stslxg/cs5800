#include <iostream>
#include <vector>
#include <limits.h>
#include <random>
#include "skiplist/skiplist.hpp"

constexpr float prob = 0.5;
static std::vector<Node*> search_helper(int key, Node* head);

SkipList::SkipList(): gen(rd()), d(prob) {
    head = new Node;
    head->val = INT_MIN;
    tail = new Node;
    tail->val = INT_MAX;
    head->next.push_back(tail);
    tail->next.push_back(nullptr);
}

void SkipList::insert(int key) {
    std::vector<Node*> res = search_helper(key, head);
    if (res[0]->next[0]->val == key)
        return;
    int i = 0;
    Node *p = new Node;
    p->val = key;
    do {
        p->next.push_back(res[i]->next[i]);
        res[i]->next[i] = p;
        if (get_rand_bit()) {
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

bool SkipList::del(int key) {
    std::vector<Node*> res = search_helper(key, head);
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

bool SkipList::lookup(int key) {
    std::vector<Node*> res = search_helper(key, head);
    if (res[0]->next[0]->val == key)
        return true;
    else
        return false;
}

void SkipList::print() {
    for (int i = 0; i < head->next.size(); i++) {
        std::cout << head->val;
        Node *p = head->next[i];
        while (p) {
            std::cout << " -> " << p->val;
            p = p->next[i];
        }
        std::cout << std::endl;
    }
}

int SkipList::get_rand_bit() {
    return d(gen);
}

Node* SkipList::search(int key) {
    std::vector<Node*> res = search_helper(key, head);
    return res[0]->next[0];
}

SkipList::~SkipList() {
    Node *p = head;
    while (p) {
        Node *q = p;
        p = p->next[0];
        delete q;
    }
}

std::vector<Node*> search_helper(int key, Node* head) {
    std::vector<Node*> prevs(head->next.size(), nullptr);
    Node *p = head;
    for (int i = head->next.size() - 1; i >= 0; i--) {
        while (p->next[i] && p->next[i]->val < key) {
            p = p->next[i];
        }
        prevs[i] = p;
    }
    return prevs;
}


