#ifndef CONTACTREPOSITORY_H
#define CONTACTREPOSITORY_H

#include "Modelo/Contacto.h"
#include <vector>
#include <string>

class ContactRepository {
private:
    std::string archivo;

public:
    explicit ContactRepository(const std::string& archivo = "contactos.txt");

    std::vector<Contacto> load();
    void save(const std::vector<Contacto>& contactos);
    void exportCSV(const std::vector<Contacto>& contactos,
                   const std::string& archivoCSV = "contactos.csv");
};

#endif
