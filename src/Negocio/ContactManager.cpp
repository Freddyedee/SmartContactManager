#include "ContactManager.h"
#include <QCoreApplication>
#include <iostream>
#include <QDir>


ContactManager::ContactManager() : nextId(1) {

    // Guardar y cargar SIEMPRE desde el directorio del ejecutable
    filePath =
        QCoreApplication::applicationDirPath().toStdString()
        + "/contactos.txt";

    loadData();
}

ContactManager::~ContactManager() {
    saveToFile(); // Guardado automático al cerrar
}
void ContactManager::loadData() {
    contactos = repositorioContactos.load();

    nextId = 1;
    for (const auto& c : contactos) {
        if (c.getId() >= nextId) {
            nextId = c.getId() + 1;
        }
    }

    rebuildIndices();
}

void ContactManager::rebuildIndices() {
    telIndex.clear();
    emailIndex.clear();
    // Trie no tiene clear fácil, idealmente se reinicializa,
    // pero aquí asumiremos que al iniciar el programa está vacío.
    // Si llamas a esto en runtime, deberías limpiar el Trie primero.

    for (const auto& c : contactos) {
        telIndex.add(c.getTelefono(), c.getId());
        emailIndex.add(c.getEmail(), c.getId());
        nameTrie.insert(c.getNombre(), c.getId());
    }
}

int ContactManager::generateId() {
    return nextId++;
}

int ContactManager::findVectorIndexById(int id) const {
    for (size_t i = 0; i < contactos.size(); ++i) {
        if (contactos[i].getId() == id) return static_cast<int>(i);
    }
    return -1;
}

bool ContactManager::create(std::string nombre,
                            std::string telefono,
                            std::string email)
{
    // 1. Validación básica
    if (nombre.empty() || telefono.empty()) {
        std::cout << "[ADD][ERROR] Nombre o teléfono vacío\n";
        return false;
    }

    // 2. Validación de formato
    if (!std::all_of(telefono.begin(), telefono.end(), ::isdigit)) {
        std::cout << "[ADD][ERROR] Teléfono debe ser numérico\n";
        return false;
    }

    if (!email.empty() && email.find('@') == std::string::npos) {
        std::cout << "[ADD][ERROR] Email inválido\n";
        return false;
    }

    // 3. Validación de duplicados (índices hash)
    if (telIndex.find(telefono) != -1) {
        std::cout << "[ADD][ERROR] Teléfono duplicado\n";
        return false;
    }

    if (!email.empty() && emailIndex.find(email) != -1) {
        std::cout << "[ADD][ERROR] Email duplicado\n";
        return false;
    }

    // 4. Crear contacto
    int id = generateId();
    Contacto c(id, nombre, telefono, email);
    contactos.push_back(c);

    // 5. Indexar (USANDO ID)
    telIndex.add(telefono, id);

    if (!email.empty()) {
        emailIndex.add(email, id);
    }

    nameTrie.insert(nombre, id);
    recents.add(id);

    // 6. Persistencia
    saveToFile();

    // 7. Log
    std::cout << "[ADD] ID=" << id
              << " | Nombre=" << nombre
              << " | Tel=" << telefono
              << " | Email=" << email << std::endl;

    return true;
}
bool ContactManager::update(int id,
                            const std::string& nuevoNombre,
                            const std::string& nuevoTel,
                            const std::string& nuevoEmail)
{
    int idx = findVectorIndexById(id);
    if (idx == -1) return false;

    Contacto& c = contactos[idx];

    // 1. Cambio de teléfono
    if (c.getTelefono() != nuevoTel) {
        int existingId = telIndex.find(nuevoTel);
        if (existingId != -1 && existingId != id) return false;

        telIndex.remove(c.getTelefono());
        telIndex.add(nuevoTel, id);
    }

    // 2. Cambio de email
    if (c.getEmail() != nuevoEmail) {
        int existingId = emailIndex.find(nuevoEmail);
        if (existingId != -1 && existingId != id) return false;

        emailIndex.remove(c.getEmail());
        emailIndex.add(nuevoEmail, id);
    }

    // 3. Cambio de nombre (Trie)
    if (c.getNombre() != nuevoNombre) {
        nameTrie.removeWord(c.getNombre(), id);
        nameTrie.insert(nuevoNombre, id);
    }

    // 4. Actualizar objeto
    c.actualizarContacto(nuevoNombre, nuevoTel, nuevoEmail);

    recents.add(id);
    saveToFile();

    return true;
}

bool ContactManager::remove(int id) {
    int idx = findVectorIndexById(id);
    if (idx == -1) return false;

    Contacto copy = contactos[idx]; // Copia para sacar datos para borrar de índices

    // Eliminar de estructuras auxiliares
    telIndex.remove(copy.getTelefono());
    emailIndex.remove(copy.getEmail());
    nameTrie.removeWord(copy.getNombre(), id);

    // Eliminar del vector principal
    contactos.erase(contactos.begin() + idx);

    saveToFile();
    return true;
}

// Búsquedas
Contacto* ContactManager::searchById(int id) {
    int idx = findVectorIndexById(id);
    if (idx == -1) return nullptr;

    recents.add(id);
    return &contactos[idx];
}

Contacto* ContactManager::searchByTel(const std::string& tel) {
    int id = telIndex.find(tel);
    if (id == -1) return nullptr;
    return searchById(id); // Reutiliza lógica de recientes
}

Contacto* ContactManager::searchByEmail(const std::string& email) {
    int id = emailIndex.find(email);
    if (id == -1) return nullptr;
    return searchById(id);
}

std::vector<Contacto> ContactManager::searchByName(const std::string& prefix) {
    std::vector<int> ids = nameTrie.searchPrefix(prefix);
    std::vector<Contacto> results;

    for (int id : ids) {
        int idx = findVectorIndexById(id);
        if (idx != -1) {
            results.push_back(contactos[idx]);
            recents.add(id); // Añadimos a recientes
        }
    }
    return results;
}

std::vector<Contacto> ContactManager::getRecentContacts() {
    std::vector<int> ids = recents.getAll();
    std::vector<Contacto> results;

    for (int id : ids) {
        int idx = findVectorIndexById(id);
        if (idx != -1) {
            results.push_back(contactos[idx]);
        }
    }
    return results;
}

void ContactManager::saveToFile() {
    repositorioContactos.save(contactos);
}

void ContactManager::exportToCSV(const std::string& csvPath)
{
    QString qPath = QString::fromStdString(csvPath);
    QString finalPath;

    if (QDir::isAbsolutePath(qPath)) {
        finalPath = qPath;
    } else {
        finalPath =
            QCoreApplication::applicationDirPath()
            + "/" + qPath;
    }

    repositorioContactos.exportCSV(contactos, finalPath.toStdString());

    std::cout << "[EXPORT] CSV generado en: "
              << finalPath.toStdString() << std::endl;
}

const std::vector<Contacto>& ContactManager::getAllContacts() const {
    return contactos;
}

bool isNumeric(const std::string& value) {
    return !value.empty() &&
           std::all_of(value.begin(), value.end(), ::isdigit);
}

bool isValidEmail(const std::string& email) {
    return email.empty() || email.find('@') != std::string::npos;
}
