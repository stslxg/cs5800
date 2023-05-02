#pragma once
#include <string>
#include <map>
#include <vector>
#include <utility>

struct Node {
    std::string word;
    int count;
    Node *prev, *next;
};

class Hash {
public:
    Hash(const unsigned int m = M): H{ m, nullptr }, m{ m } {};
    virtual void insert(const std::string& word, int count);
    void del(const std::string& word);
    void increase(const std::string& word);
    int find(const std::string& word) const;
    std::map<int, int> hist() const;
    std::vector<std::string> list_all_keys() const;
    std::vector<std::pair<std::string, int>> list() const;
    ~Hash();
private:
    static constexpr unsigned int M = 1000;
    const unsigned int m;
    std::vector<Node*> H;
    virtual int hash(const std::string& word) const;
    Node* search(const std::string& word) const;
};
