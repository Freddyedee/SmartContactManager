#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>
#include <limits>

ConsoleUI::ConsoleUI(ContactManager* mgr) : manager(mgr) {}

void ConsoleUI::run() {
    std::cout << "====================================\n";
    std::cout << "   Directorio Inteligente de Contactos\n";
    std::cout << "====================================\n\n";

    while (true) {
        showMainMenu();
        int option;
        std::cout << "\nSeleccione una opcion (1-8): ";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (option) {
        case 1: handleCreate(); break;
        case 2: handleSearchByName(); break;
        case 3: handleSearchByTel(); break;
        case 4: handleSearchByEmail(); break;
        case 5: handleUpdate(); break;
        case 6: handleDelete(); break;
        case 7: handleShowRecents(); break;
        case 8: handleExportCSV(); break;
        case 0:
            manager->saveToFile();
            std::cout << "\n¡Datos guardados! Hasta luego.\n";
            return;
        default:
            std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
        std::cout << "\nPresione Enter para continuar...";
        std::cin.get();
    }
}

void ConsoleUI::showMainMenu() const {
    std::cout << "\n--- Menu Principal ---\n";
    std::cout << "1. Crear nuevo contacto\n";
    std::cout << "2. Buscar por nombre (parcial)\n";
    std::cout << "3. Buscar por telefono\n";
    std::cout << "4. Buscar por email\n";
    std::cout << "5. Actualizar contacto\n";
    std::cout << "6. Eliminar contacto\n";
    std::cout << "7. Ver contactos recientes\n";
    std::cout << "8. Exportar a CSV\n";
    std::cout << "0. Salir y guardar\n";
}

void ConsoleUI::handleCreate() {
    std::cout << "\n--- Crear Contacto ---\n";
    std::string nombre = readNonEmptyString("Nombre: ");
    std::string tel    = readNonEmptyString("Telefono: ");
    std::string email  = readNonEmptyString("Email: ");

    Contacto nuevo(nombre, tel, email);
    if (manager->create(nuevo)) {
        std::cout << "Contacto creado exitosamente!\n";
    } else {
        std::cout << "Error: Ya existe un contacto con ese telefono o email.\n";
    }
}

void ConsoleUI::handleUpdate() {
    std::cout << "\n--- Actualizar Contacto ---\n";
    std::string tel = readNonEmptyString("Ingrese telefono del contacto a modificar: ");
    Contacto* c = manager->searchByTel(tel);
    if (!c) {
        std::cout << "Contacto no encontrado.\n";
        return;
    }

    showContact(*c);
    std::cout << "\nDeje en blanco los campos que no desea cambiar.\n";

    std::string nuevoNombre = readNonEmptyString("Nuevo nombre (Enter para mantener): ");
    std::string nuevoTel    = readNonEmptyString("Nuevo telefono (Enter para mantener): ");
    std::string nuevoEmail  = readNonEmptyString("Nuevo email (Enter para mantener): ");

    Contacto updated = *c;
    if (!nuevoNombre.empty()) updated.nombre = nuevoNombre;
    if (!nuevoTel.empty())    updated.telefono = nuevoTel;
    if (!nuevoEmail.empty())  updated.email = nuevoEmail;

    // Como searchByTel ya actualizó ultimoAcceso, solo actualizamos
    size_t idx = manager->getIndexByTel(tel);
    if (manager->update(idx, updated)) {
        std::cout << "Contacto actualizado!\n";
    } else {
        std::cout << "Error al actualizar.\n";
    }
}

void ConsoleUI::handleDelete() {
    std::cout << "\n--- Eliminar Contacto ---\n";
    std::string key = readNonEmptyString("Telefono o email del contacto: ");
    Contacto* c = manager->searchByTel(key);
    if (!c) c = manager->searchByEmail(key);
    if (!c) {
        std::cout << "No encontrado.\n";
        return;
    }

    showContact(*c);
    std::cout << "¿Eliminar este contacto? (s/n): ";
    char confirm;
    std::cin >> confirm;
    if (confirm == 's' || confirm == 'S') {
            size_t idx = manager->getIndexByPointer(c);
        if (manager->remove(idx)) {
            std::cout << "Contacto eliminado.\n";
        } else {
            std::cout << "Error al eliminar.\n";
        }
    }
}

void ConsoleUI::handleSearchByName() {
    std::cout << "\n--- Busqueda por Nombre (parcial) ---\n";
    std::string prefix = readNonEmptyString("Ingrese parte del nombre: ");
    auto results = manager->searchByName(prefix);
    if (results.empty()) {
        std::cout << "No se encontraron contactos.\n";
    } else {
        std::cout << "Resultados (" << results.size() << "):\n";
        showContacts(results);
    }
}

void ConsoleUI::handleSearchByTel() {
    std::cout << "\n--- Busqueda por Telefono ---\n";
    std::string tel = readNonEmptyString("Telefono: ");
    Contacto* c = manager->searchByTel(tel);
    if (c) {
        showContact(*c);
    } else {
        std::cout << "No encontrado.\n";
    }
}

void ConsoleUI::handleSearchByEmail() {
    std::cout << "\n--- Busqueda por Email ---\n";
    std::string email = readNonEmptyString("Email: ");
    Contacto* c = manager->searchByEmail(email);
    if (c) {
        showContact(*c);
    } else {
        std::cout << "No encontrado.\n";
    }
}

void ConsoleUI::handleShowRecents() {
    std::cout << "\n--- Contactos Recientes (ultimos 20) ---\n";
    auto recents = manager->getRecentContacts();
    if (recents.empty()) {
        std::cout << "Aun no hay contactos recientes.\n";
    } else {
        showContacts(recents);
    }
}

void ConsoleUI::handleExportCSV() {
    std::string path = readNonEmptyString("Ruta para guardar el CSV (ej: contactos.csv): ");
    manager->exportToCSV(path);
    std::cout << "Exportado correctamente a " << path << "\n";
}

void ConsoleUI::showContact(const Contacto& c, bool withIndex, size_t index) const {
    if (withIndex) std::cout << "[" << index << "] ";
    std::cout << "Nombre: " << c.nombre << "\n";
    std::cout << "Telefono: " << c.telefono << "\n";
    std::cout << "Email: " << c.email << "\n";
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", std::localtime(&c.fechaCreacion));
    std::cout << "Creado: " << buf << "\n";
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", std::localtime(&c.ultimoAcceso));
    std::cout << "Ultimo acceso: " << buf << "\n\n";
}

void ConsoleUI::showContacts(const std::vector<Contacto>& contacts, bool withIndex) const {
    for (size_t i = 0; i < contacts.size(); ++i) {
        showContact(contacts[i], withIndex, i);
    }
}

std::string ConsoleUI::readNonEmptyString(const std::string& prompt) const {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (!input.empty()) return input;
        std::cout << "Este campo no puede estar vacio. Intente nuevamente.\n";
    }
}

size_t ConsoleUI::readIndex(const std::string& prompt, size_t max) const {
    size_t idx;
    while (true) {
        std::cout << prompt;
        if (std::cin >> idx && idx < max) {
            std::cin.ignore();
            return idx;
        }
        std::cout << "Indice invalido. Debe ser entre 0 y " << max-1 << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
