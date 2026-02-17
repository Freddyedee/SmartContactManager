#include "include/Modelo/Contacto.h"

Contacto::Contacto() : id(0) {}

Contacto::Contacto(int id,
                   const std::string& nombre,
                   const std::string& telefono,
                   const std::string& email)
    : id(id), nombre(nombre), telefono(telefono), email(email) {}

    int Contacto::getId() const {
        return id; }

    std::string Contacto::getNombre() const {
        return nombre; }

    std::string Contacto::getTelefono() const {
        return telefono; }

    std::string Contacto::getEmail() const {
        return email; }

    void Contacto::setNombre(const std::string& nombre) {
        this->nombre = nombre;
        this->ultimaModificacion = std::time(nullptr);
    }

    void Contacto::setTelefono(const std::string& telefono) {
        this->telefono = telefono;
        this->ultimaModificacion = std::time(nullptr);
    }

    void Contacto::setEmail(const std::string& email) {
        this->email = email;
        this->ultimaModificacion = std::time(nullptr);
    }

    std::time_t Contacto::getUltimaModificacion() const {
        return ultimaModificacion;
    }

    void Contacto::actualizarContacto(const std::string& nombre,
                                  const std::string& telefono,
                                  const std::string& email){
        this->nombre = nombre;
        this->telefono = telefono;
        this->email = email;
        this->ultimaModificacion = std::time(nullptr);
    }
