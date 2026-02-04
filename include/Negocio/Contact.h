#ifndef CONTACT_H
#define CONTACT_H

#include <string>

struct Contact {

    std::string nombre;
    std::string telefono;
    std::string email;
    time_t fechaCreacion;
    time_t ultimoAcceso;
};

#endif // CONTACT_H
