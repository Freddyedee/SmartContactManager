#include "Datos/ContactRepository.h"
#include <fstream>
#include <sstream>
#include <iostream>

ContactRepository::ContactRepository(const std::string& archivo)
    : archivo(archivo) {}

std::vector<Contacto> ContactRepository::load() {
    std::vector<Contacto> contactos;
    std::ifstream file(archivo);

    if (!file.is_open()) return contactos;

    std::string linea;
    while (std::getline(file, linea)) {

        if (linea.empty()) continue; // ⬅️ IMPORTANTE

        std::stringstream ss(linea);
        std::string idStr, nombre, tel, email;

        if (!std::getline(ss, idStr, ';')) continue;
        if (!std::getline(ss, nombre, ';')) continue;
        if (!std::getline(ss, tel, ';')) continue;
        if (!std::getline(ss, email, ';')) continue;

        // Evitar cabeceras o basura
        //if (!std::all_of(idStr.begin(), idStr.end(), ::isdigit))
        //  continue;

        int id = std::stoi(idStr);
        contactos.emplace_back(id, nombre, tel, email);
    }

    return contactos;
}

void ContactRepository::save(const std::vector<Contacto>& contactos) {
    std::ofstream file(archivo);
    for (const auto& c : contactos) {
        file << c.getId() << ";"
             << c.getNombre() << ";"
             << c.getTelefono() << ";"
             << c.getEmail() << "\n";
    }
}

void ContactRepository::exportCSV(
    const std::vector<Contacto>& contactos,
    const std::string& archivoCSV)
{
    std::ofstream file(archivoCSV);

    if (!file.is_open()) {
        std::cerr << "[EXPORT][ERROR] No se pudo crear el archivo: "
                  << archivoCSV << std::endl;
        return;
    }

    file << "ID;Nombre;Telefono;Email\n";

    for (const auto& c : contactos) {
        file << c.getId() << ";"
             << c.getNombre() << ";"
             << c.getTelefono() << ";"
             << c.getEmail() << "\n";
    }
}
