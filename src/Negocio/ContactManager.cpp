#include "ContactManager.h"
#include <algorithm>

ContactManager::ContactManager() {
    contacts = repo.load(filePath);
    rebuildIndices();
}

void ContactManager::rebuildIndices() {
    telIndex.clear();
    emailIndex.clear();
    for (size_t i = 0; i < contacts.size(); ++i) {
        telIndex.add(contacts[i].telefono, i);
        emailIndex.add(contacts[i].email, i);
        nameTrie.insert(contacts[i].nombre, i);
    }
}

bool ContactManager::create(const Contacto& c) {
    if (telIndex.find(c.telefono) != static_cast<size_t>(-1) ||
        emailIndex.find(c.email) != static_cast<size_t>(-1))
        return false;

    size_t idx = contacts.size();
    contacts.push_back(c);
    telIndex.add(c.telefono, idx);
    emailIndex.add(c.email, idx);
    nameTrie.insert(c.nombre, idx);
    recents.add(idx);
    return true;
}

bool ContactManager::update(size_t index, const Contacto& updated) {
    if (index >= contacts.size()) return false;

    // Si cambia teléfono o email, actualizar índices
    if (contacts[index].telefono != updated.telefono) {
        telIndex.remove(contacts[index].telefono);
        telIndex.add(updated.telefono, index);
    }
    if (contacts[index].email != updated.email) {
        emailIndex.remove(contacts[index].email);
        emailIndex.add(updated.email, index);
    }
    // Si cambia nombre, reconstruir Trie (simple pero efectivo)
    if (contacts[index].nombre != updated.nombre) {
        rebuildIndices();
    }

    contacts[index] = updated;
    contacts[index].actualizarUltimoAcceso();
    recents.add(index);
    return true;
}

bool ContactManager::remove(size_t index) {
    if (index >= contacts.size()) return false;
    telIndex.remove(contacts[index].telefono);
    emailIndex.remove(contacts[index].email);
    // Trie se reconstruye completo (más simple que borrar nodos)
    contacts.erase(contacts.begin() + index);
    rebuildIndices();
    return true;
}

Contacto* ContactManager::searchByTel(const std::string& tel) {
    size_t idx = telIndex.find(tel);
    if (idx == static_cast<size_t>(-1)) return nullptr;
    contacts[idx].actualizarUltimoAcceso();
    recents.add(idx);
    return &contacts[idx];
}

Contacto* ContactManager::searchByEmail(const std::string& email) {
    size_t idx = emailIndex.find(email);
    if (idx == static_cast<size_t>(-1)) return nullptr;
    contacts[idx].actualizarUltimoAcceso();
    recents.add(idx);
    return &contacts[idx];
}

std::vector<Contacto> ContactManager::searchByName(const std::string& prefix) {
    auto indices = nameTrie.searchPrefix(prefix);
    std::vector<Contacto> result;
    for (auto i : indices) {
        contacts[i].actualizarUltimoAcceso();
        recents.add(i);
        result.push_back(contacts[i]);
    }
    return result;
}

std::vector<Contacto> ContactManager::getRecentContacts() {
    std::vector<size_t> ids = recents.getAll();
    std::vector<Contacto> result;
    for (auto i : ids) result.push_back(contacts[i]);
    return result;
}

void ContactManager::saveToFile() {
    repo.save(contacts, filePath);
}

void ContactManager::exportToCSV(const std::string& csvPath) {
    repo.exportCSV(contacts, csvPath);
}

size_t ContactManager::getIndexByPointer(const Contacto* contact) const {
    if (!contact) return static_cast<size_t>(-1);
    auto it = std::find_if(contacts.begin(), contacts.end(),
                           [contact](const Contacto& c) { return &c == contact; });
    return (it != contacts.end()) ? std::distance(contacts.begin(), it) : static_cast<size_t>(-1);
}

size_t ContactManager::getIndexByTel(const std::string& tel) const {
    size_t idx = telIndex.find(tel);
    return idx;
}
