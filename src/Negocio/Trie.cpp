#include "Trie.h"
#include <algorithm>

Trie::Trie() { root = new Node(); }

Trie::~Trie() { deleteTrie(root); }

void Trie::deleteTrie(Node* node) {
    if (!node) return;
    for (auto& p : node->children) {
        deleteTrie(p.second);
    }
    delete node;
}

void Trie::insert(const std::string& word, int id) {
    Node* curr = root;
    for (char ch : word) {
        // Convertimos a minúsculas para búsqueda insensible a mayúsculas si lo deseas
        // ch = tolower(ch);
        if (curr->children.find(ch) == curr->children.end())
            curr->children[ch] = new Node();
        curr = curr->children[ch];
    }
    curr->isEnd = true;
    curr->contactIds.push_back(id);
}

// Nueva función crítica para el Update/Delete
void Trie::removeWord(const std::string& word, int id) {
    Node* curr = root;
    for (char ch : word) {
        if (curr->children.find(ch) == curr->children.end()) return; // No existe
        curr = curr->children[ch];
    }

    if (curr->isEnd) {
        // Buscamos el ID en el vector del nodo y lo eliminamos
        auto& ids = curr->contactIds;
        auto it = std::remove(ids.begin(), ids.end(), id);
        ids.erase(it, ids.end());

        // Si ya no quedan IDs en este nodo, ya no es final de palabra efectiva
        if (ids.empty()) {
            curr->isEnd = false;
        }
    }
}

void Trie::collectIds(Node* node, std::vector<int>& results) {
    if (node->isEnd) {
        for (int id : node->contactIds) {
            results.push_back(id);
        }
    }
    for (auto& p : node->children) {
        collectIds(p.second, results);
    }
}

std::vector<int> Trie::searchPrefix(const std::string& prefix) {
    Node* curr = root;
    for (char ch : prefix) {
        auto it = curr->children.find(ch);
        if (it == curr->children.end()) return {}; // Prefijo no encontrado
        curr = it->second;
    }

    std::vector<int> results;
    collectIds(curr, results);
    return results;
}
