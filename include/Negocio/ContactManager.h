#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include "Modelo/Contacto.h"
#include "Trie.h"
#include "ContactIndex.h"
#include "Datos/ContactRepository.h"
#include "RecentContacts.h"

#include <vector>
#include <string>

class ContactManager {

private:
    std::vector<Contacto> contactos; // Almacenamiento principal de memorio

    //Indices auxiliares para busquedas rapidas
    ContactIndex telIndex;
    ContactIndex emailIndex;
    Trie nameTrie;
    RecentContacts recents;
    std::string filePath ;

    // Persistencia (Datos)
    ContactRepository repositorioContactos;


    int nextId;

    int generateId();
    void rebuildIndices(); //Reconstruye indices al cargar el archivo
    int findVectorIndexById(int id) const; // Encuentra la posición en el vector dado n ID, retorna -1 en caso de inexistencia.

public:
    ContactManager();
    ~ContactManager() ;

    //Inicialización
    void loadData(); // Carga de datos al iniciar

    // CRUD --- Create / Remove / Upload / Delete

    //Create
    bool create(std::string nombre, std::string telefono, std::string email);

    //Update, Busqueda por Id.
    bool update(int id, const std::string& nuevoNombre, const std::string& nuevoTel, const std::string& nuevoEmail);

    //Remove
    bool remove(int id);

    //Busquedas

    Contacto* searchById(int id);
    Contacto* searchByTel(const std::string& tel);
    Contacto* searchByEmail(const std::string& email);


    //Buqueda parcial por nombres.
    std::vector<Contacto> searchByName(const std::string& prefix);


    //Contactos recientes
    std::vector<Contacto> getRecentContacts();

    //Persistencia
    void saveToFile();
    void exportToCSV(const std::string& csvPath);

    //  Obtener todos los contactos.
    const std::vector<Contacto>& getAllContacts() const;




    //EN DUDA!
    size_t getIndexByPointer(const Contacto* contact) const;
    size_t getIndexByTel(const std::string& tel) const;




};
#endif // CONTACTMANAGER_H
