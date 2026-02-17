#ifndef CONTACTO_H
#define CONTACTO_H

#include <string>
#include <ctime>

class Contacto {
private:
    int id;
    std::string nombre;
    std::string telefono;
    std::string email;
    std::time_t ultimaModificacion;

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
    std::time_t getUltimaModificacion() const; // Getter para la fecha

    // Setters
    void setNombre(const std::string& nombre);
    void setTelefono(const std::string& telefono);
    void setEmail(const std::string& email);

    //Metodo
    void actualizarContacto(const std::string& nombre,
                            const std::string& telefono,
                            const std::string& email);
};

#endif
