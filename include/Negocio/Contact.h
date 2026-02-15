#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <ctime>

class Contacto {
public:
    std::string nombre;
    std::string telefono;
    std::string email;
    time_t fechaCreacion;
    time_t ultimoAcceso;

    Contacto();
    Contacto(const std::string& n, const std::string& t, const std::string& e);

    void actualizarUltimoAcceso();
    std::string toFileString() const;
    static Contacto fromFileString(const std::string& line);
};

#endif // CONTACT_H
