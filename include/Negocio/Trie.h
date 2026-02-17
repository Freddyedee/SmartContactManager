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
        std::vector<int> contactIds; // Lista de IDs que coinciden con este prefijo
    };
    Node* root;

    void deleteTrie(Node* node);
    // Helper para recolectar todos los IDs bajo un nodo

public:
    Trie();
    ~Trie();

    // Inserta una palabra asociada a un ID
    void insert(const std::string& word, int id);

    // Elimina una asociación palabra-ID (necesario para updates/deletes)
    void removeWord(const std::string& word, int id);

    void collectIds(Node* node, std::vector<int>& results);

    std::vector<int> searchPrefix(const std::string& prefix);
};

#endif // TRIE_H
