#ifndef CONTACTINDEX_H
#define CONTACTINDEX_H

#include <unordered_map>
#include <string>

class ContactIndex {
private:
    //Trabaja con mapear clave (telefono, email) -> ID contacto.
    std::unordered_map<std::string, int> data;
public:
    void add(const std::string& key, int index);
    void remove(const std::string& key);
    int find(const std::string& key) const;
    void clear();
};
#endif // CONTACTINDEX_H
