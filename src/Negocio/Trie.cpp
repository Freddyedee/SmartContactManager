#include "Trie.h"

Trie::Trie() { root = new Node(); }

Trie::~Trie() { deleteTrie(root); }

void Trie::deleteTrie(Node* node) {
    for (auto& p : node->children) deleteTrie(p.second);
    delete node;
}

void Trie::insert(const std::string& word, size_t index) {
    Node* curr = root;
    for (char ch : word) {
        if (curr->children.find(ch) == curr->children.end())
            curr->children[ch] = new Node();
        curr = curr->children[ch];
    }
    curr->isEnd = true;
    curr->indices.push_back(index);
}

void Trie::collectWords(Node* node, std::vector<size_t>& results) {
    if (node->isEnd) {
        for (auto idx : node->indices) results.push_back(idx);
    }
    for (auto& p : node->children)
        collectWords(p.second, results);
}

std::vector<size_t> Trie::searchPrefix(const std::string& prefix) {
    Node* curr = root;
    for (char ch : prefix) {
        auto it = curr->children.find(ch);
        if (it == curr->children.end()) return {};
        curr = it->second;
    }
    std::vector<size_t> results;
    collectWords(curr, results);
    return results;
}
