#include "ContactIndex.h"

void ContactIndex::add(const std::string& key, size_t index) {
    data[key] = index;
}

void ContactIndex::remove(const std::string& key) {
    data.erase(key);
}

size_t ContactIndex::find(const std::string& key) const {
    auto it = data.find(key);
    return it != data.end() ? it->second : static_cast<size_t>(-1);
}

void ContactIndex::clear() {
    data.clear();
}
