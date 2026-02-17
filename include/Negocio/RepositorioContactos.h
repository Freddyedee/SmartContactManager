#ifndef REPOSITORIOCONTACTOS_H
#define REPOSITORIOCONTACTOS_H

#include <unordered_map>
#include <fstream>
#include <vector>
#include "Modelo/Contacto.h"

/**
 * @class RepositorioContactos
 * @brief Gestiona la persistencia de los contactos.
 *
 * Esta clase se encarga de guardar los contactos en un archivo y cargarlos desde dicho archivo.
 * Utiliza un mapa (`unordered_map`) para almacenar los contactos en memoria, permitiendo accesos rápidos.
 */
class RepositorioContactos {

private:
    std::unordered_map<std::string, Contacto> contactos;  /**< Mapa de contactos indexados por nombre */

public:
    /**
     * @brief Guarda los contactos en un archivo.
     * @param archivo Ruta al archivo donde se guardarán los contactos.
     */
    void guardarContactos(const std::string& archivo, const std::vector<Contacto>& contactos);

    /**
     * @brief Carga los contactos desde un archivo.
     * @param archivo Ruta al archivo desde donde se cargarán los contactos.
     */
    std::vector<Contacto> cargarContactos(const std::string& archivo);

    // Exportar a CSV
    void exportarCSV(const std::string& archivo, const std::vector<Contacto>& contactos);


};
#endif // REPOSITORIOCONTACTOS_H
