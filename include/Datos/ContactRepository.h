#ifndef CONTACTREPOSITORY_H
#define CONTACTREPOSITORY_H
#include "include/Negocio/Contact.h"
#include <vector>
#include <string>

class ContactRepository {
    public:
    static std::vector<Contact> cargar(const std::string& nombreArchivo = "contactos.txt");
    static void guardar(const std::vector<Contact>& contactos, const std::string& nombreArchivo = "contactos.txt");
    static void exportarCSV(const std::vector<Contact>& contactos, const std::string& nombreArchivo = "contactos.csv");

};



#endif // CONTACTREPOSITORY_H
