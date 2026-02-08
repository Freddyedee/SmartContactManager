#include "include/Datos/ContactRepository.h"
#include <fstream>
#include <sstream>
#include <string>

std::vector<Contacto> ContactRepository::load(const std::string& nombreArchivo){

    std::vector<Contacto> contactos; //Creamos una variable de tipo contact que a su vez es un vector
    std::ifstream archivo (nombreArchivo);
    std::string linea;

    if(!archivo.is_open()){
            return contactos;
    };

    while(std::getline(archivo, linea)){
        std::stringstream ss(linea);
        Contacto c;
        std::getline(ss, c.nombre, ';');
        std::getline(ss, c.telefono, ';');
        std::getline(ss, c.email, ';');
        contactos.push_back(c);
    }
    archivo.close();
    return contactos;
}

void ContactRepository::save(const std::vector<Contacto>& contactos, const std::string& nombreArchivo){
    std::ofstream archivo(nombreArchivo);
    for(const auto& c : contactos){
        archivo << c.nombre << ";" << c.telefono << ";" << c.email << "\n";
    }
    archivo.close();
}

void ContactRepository::exportCSV(const std::vector<Contacto>& contactos, const std::string& nombreArchivo){

    std::ofstream archivo(nombreArchivo);
    archivo << "Nombre;Telefono;Email\n"; //Cabecera
    for(const auto& c : contactos){
        archivo << c.nombre << ";" << c.telefono << ";" << c.email << "\n";
    }
    archivo.close();
}

