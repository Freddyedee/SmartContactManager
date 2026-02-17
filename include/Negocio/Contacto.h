#ifndef CONTACTO_H
#define CONTACTO_H

#include <string>

class Contacto {
private:
    int id;
    std::string nombre;
    std::string telefono;
    std::string email;

public:
    Contacto();
    Contacto(int id,
             const std::string& nombre,
             const std::string& telefono,
             const std::string& email);

    // Getters
    int getId() const;
    std::string getNombre() const;
    std::string getTelefono() const;
    std::string getEmail() const;

    // Setters
    void setNombre(const std::string& nombre);
    void setTelefono(const std::string& telefono);
    void setEmail(const std::string& email);
};

#endif
