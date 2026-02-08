#ifndef CONTACTINDEX_H
#define CONTACTINDEX_H

#include <unordered_map>
#include <string>

class ContactIndex {
private:
    std::unordered_map<std::string, size_t> data;
public:
    void add(const std::string& key, size_t index);
    void remove(const std::string& key);
    size_t find(const std::string& key) const;
    void clear();
};
#endif // CONTACTINDEX_H
