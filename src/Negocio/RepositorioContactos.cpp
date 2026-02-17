#include "RepositorioContactos.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Formato de archivo: ID,Nombre,Telefono,Email,Timestamp

void RepositorioContactos::guardarContactos(const std::string& archivo, const std::vector<Contacto>& contactos) {
    std::ofstream outFile(archivo);
    if (!outFile) {
        std::cerr << "Error: No se pudo abrir el archivo para escritura: " << archivo << "\n";
        return;
    }

    for (const auto& c : contactos) {
        outFile << c.getId() << ","
                << c.getNombre() << ","
                << c.getTelefono() << ","
                << c.getEmail() << ","
                << c.getUltimaModificacion() << "\n"; // Asegúrate que la fecha no tenga saltos de línea internos
    }
    outFile.close();
}

std::vector<Contacto> RepositorioContactos::cargarContactos(const std::string& archivo) {
    std::vector<Contacto> listaCargada;
    std::ifstream inFile(archivo);

    if (!inFile) {
        // Si el archivo no existe, retornamos lista vacía sin error (primer uso)
        return listaCargada;
    }

    std::string linea;
    while (std::getline(inFile, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string segmento;

        // Variables temporales
        std::string idStr, nombre, telefono, email, fecha;

        // Parseo básico de CSV
        if (std::getline(ss, idStr, ',') &&
            std::getline(ss, nombre, ',') &&
            std::getline(ss, telefono, ',') &&
            std::getline(ss, email, ',')) {

            // Leemos el resto de la línea como fecha (por si tiene comas o espacios extra)
            std::getline(ss, fecha);

            try {
                int id = std::stoi(idStr);
                Contacto nuevo(id, nombre, telefono, email);
                nuevo.setUltimaModificacion(fecha);
                listaCargada.push_back(nuevo);
            } catch (...) {
                std::cerr << "Error parseando linea: " << linea << "\n";
            }
        }
    }
    inFile.close();
    return listaCargada;
}

void RepositorioContactos::exportarCSV(const std::string& archivo, const std::vector<Contacto>& contactos) {
    // Reutilizamos la lógica, quizás con cabeceras para Excel
    std::ofstream outFile(archivo);
    if (!outFile) return;

    outFile << "ID,Nombre,Telefono,Email,Ultima Modificacion\n"; // Cabecera
    for (const auto& c : contactos) {
        outFile << c.getId() << ","
                << c.getNombre() << ","
                << c.getTelefono() << ","
                << c.getEmail() << ","
                << c.getUltimaModificacion() << "\n";
    }
    outFile.close();
}

