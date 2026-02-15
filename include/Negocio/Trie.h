#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <map>

class Trie {
private:
    struct Node {
        std::map<char, Node*> children;
        bool isEnd = false;
        std::vector<size_t> indices;
    };
    Node* root;

    void deleteTrie(Node* node);
    void collectWords(Node* node, std::vector<size_t>& results);

public:
    Trie();
    ~Trie();
    void insert(const std::string& word, size_t index);
    std::vector<size_t> searchPrefix(const std::string& prefix);
};

#endif // TRIE_H
