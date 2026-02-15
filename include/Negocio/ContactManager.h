#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H
#include "Contact.h"
#include "Trie.h"
#include "ContactIndex.h"
#include "RecentContacts.h"
#include "ContactRepository.h"
#include <vector>
#include <string>

class ContactManager {
private:
    std::vector<Contacto> contacts;
    ContactIndex telIndex;
    ContactIndex emailIndex;
    Trie nameTrie;
    RecentContacts recents;
    ContactRepository repo;
    std::string filePath = "contactos.txt";

    void rebuildIndices();

public:
    ContactManager();
    ~ContactManager() = default;

    bool create(const Contacto& c);
    bool update(size_t index, const Contacto& updated);
    bool remove(size_t index);
    Contacto* searchByTel(const std::string& tel);
    Contacto* searchByEmail(const std::string& email);
    std::vector<Contacto> searchByName(const std::string& prefix);
    std::vector<Contacto> getRecentContacts();
    void saveToFile();
    void exportToCSV(const std::string& csvPath);

    size_t getIndexByPointer(const Contacto* contact) const;
    size_t getIndexByTel(const std::string& tel) const;
};
#endif // CONTACTMANAGER_H
