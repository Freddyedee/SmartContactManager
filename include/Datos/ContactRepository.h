#ifndef CONTACTREPOSITORY_H
#define CONTACTREPOSITORY_H
#include "include/Negocio/Contact.h"
#include <vector>
#include <string>

class ContactRepository {
    public:
    static std::vector<Contacto> load(const std::string& nombreArchivo = "contactos.txt");
    static void save(const std::vector<Contacto>& contactos, const std::string& nombreArchivo = "contactos.txt");
    static void exportCSV(const std::vector<Contacto>& contactos, const std::string& nombreArchivo = "contactos.csv");

};



#endif // CONTACTREPOSITORY_H
