#include "include/Datos/ContactRepository.h"
#include <iostream>

int main() {
    auto contactos = ContactRepository::cargar();
    std::cout << "Contactos cargados: " << contactos.size() << "\n";

    Contact nuevo{"Juan Pérez", "123456789", "juan@example.com"};
    Contact nuevo2{"Freddy", "04249545985", "Fre@gmail.com"};
    Contact nuevo3{"Alejandro", "04249545985", "Fre@gmail.com"};

    contactos.push_back(nuevo);
    contactos.push_back(nuevo2);
    contactos.push_back(nuevo3);

    ContactRepository::guardar(contactos);
    ContactRepository::exportarCSV(contactos);

    std::cout << "Contactos cargados: " << contactos.size() << "\n";
    return 0;
}
