#include "Contact.h"
#include <sstream>
#include <stdexcept>
#include <vector>

Contacto::Contacto() : fechaCreacion(0), ultimoAcceso(0) {}

Contacto::Contacto(const std::string& n, const std::string& t, const std::string& e)
    : nombre(n), telefono(t), email(e) {
    fechaCreacion = time(nullptr);
    ultimoAcceso = fechaCreacion;
}

void Contacto::actualizarUltimoAcceso() {
    ultimoAcceso = time(nullptr);
}

std::string Contacto::toFileString() const {
    return nombre + ";" + telefono + ";" + email + ";" +
           std::to_string(fechaCreacion) + ";" + std::to_string(ultimoAcceso);
}

Contacto Contacto::fromFileString(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(ss, token, ';')) parts.push_back(token);
    if (parts.size() != 5) throw std::runtime_error("Línea inválida: " + line);

    Contacto c;
    c.nombre = parts[0];
    c.telefono = parts[1];
    c.email = parts[2];
    c.fechaCreacion = std::stoll(parts[3]);
    c.ultimoAcceso = std::stoll(parts[4]);
    return c;
}
