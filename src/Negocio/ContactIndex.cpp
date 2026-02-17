#include "ContactIndex.h"

void ContactIndex::add(const std::string& key, int id) {
    // Si ya existe, se sobrescribe (asumimos validación previa en Manager)
    data[key] = id;
}

void ContactIndex::remove(const std::string& key) {
    data.erase(key);
}

int ContactIndex::find(const std::string& key) const {
    auto it = data.find(key);
    // Retornamos -1 si no se encuentra (estándar para "no encontrado" con enteros)
    return it != data.end() ? it->second : -1;
}

void ContactIndex::clear() {
    data.clear();
}
