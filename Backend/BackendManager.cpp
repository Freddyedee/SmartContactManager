#include "Backend/backendmanager.h"
#include <QDebug>

BackendManager::BackendManager(QObject* parent)
    : QObject(parent)
{
    // Carga inicial de contactos desde archivo (si existe)
    manager.loadData();
}

/* =========================
 *  CRUD
 * ========================= */

bool BackendManager::addContact(const QString& nombre,
                                const QString& telefono,
                                const QString& email)
{
    bool ok = manager.create(
        nombre.toStdString(),
        telefono.toStdString(),
        email.toStdString()
        );

    if (ok) {
        const auto& contactos = manager.getAllContacts();
        const Contacto& c = contactos.back(); // último agregado

        logAction("ADD", c);
    } else {
        qWarning() << "[ADD] Falló: posible duplicado"
                   << "Tel=" << telefono
                   << "Email=" << email;
    }

    return ok;
}

QVariantList BackendManager::getContacts()
{
    return getAllContacts();
}

bool BackendManager::updateContact(int id,
                                   const QString& nombre,
                                   const QString& telefono,
                                   const QString& email)
{
    bool ok = manager.update(
        id,
        nombre.toStdString(),
        telefono.toStdString(),
        email.toStdString()
        );

    if (ok) {
        Contacto* c = manager.searchById(id);
        if (c) {
            logAction("UPDATE", *c);
        }
    } else {
        qWarning() << "[UPDATE] Falló para ID=" << id;
    }

    return ok;
}

bool BackendManager::deleteContact(int id)
{
    Contacto* c = manager.searchById(id);
    if (!c) {
        qWarning() << "[DELETE] ID no encontrado:" << id;
        return false;
    }

    Contacto copia = *c; // copiar antes de borrar
    bool ok = manager.remove(id);

    if (ok) {
        logAction("DELETE", copia);
    }

    return ok;
}

/* =========================
 *  Consultas
 * ========================= */

QVariantList BackendManager::getAllContacts()
{
    QVariantList list;
    const auto& contactos = manager.getAllContacts();

    for (const auto& c : contactos) {
        list.append(contactoToMap(c));
    }

    return list;
}

QVariantList BackendManager::searchByName(const QString& prefix)
{
    qDebug() << "[SEARCH-NAME] Prefix =" << prefix;
    QVariantList list;
    auto resultados = manager.searchByName(prefix.toStdString());

    for (const auto& c : resultados) {
        list.append(contactoToMap(c));
    }

    return list;
}

QVariantList BackendManager::getRecentContacts()
{
    QVariantList list;
    auto recientes = manager.getRecentContacts();

    for (const auto& c : recientes) {
        list.append(contactoToMap(c));
    }

    return list;
}


QVariantMap BackendManager::searchByTelOrEmail(const QString& value) {

    qDebug() << "[SEARCH] Value =" << value;
    QVariantMap result;

    if (value.trimmed().isEmpty())
        return result;

    Contacto* c = nullptr;
    std::string v = value.toStdString();

    if (value.contains("@")) {
        c = manager.searchByEmail(v);
    } else {
        c = manager.searchByTel(v);
    }

    if (c) {
        result = contactoToMap(*c);
    }

    return result;
}



/* =========================
 *  Exportación
 * ========================= */

void BackendManager::exportCSV(const QString& path)
{

    manager.exportToCSV(path.toStdString());
    qDebug() << "[EXPORT] CSV generado en:" << path;
}

/* =========================
 *  Helpers
 * ========================= */

QVariantMap BackendManager::contactoToMap(const Contacto& c)
{
    QVariantMap map;
    map["id"] = c.getId();
    map["nombre"] = QString::fromStdString(c.getNombre());
    map["telefono"] = QString::fromStdString(c.getTelefono());
    map["email"] = QString::fromStdString(c.getEmail());
    return map;
}

void BackendManager::logAction(const QString& action, const Contacto& c) {
    qDebug().noquote()
    << "[" << action << "]"
    << "ID=" << c.getId()
    << "| Nombre=" << QString::fromStdString(c.getNombre())
    << "| Tel=" << QString::fromStdString(c.getTelefono())
    << "| Email=" << QString::fromStdString(c.getEmail());
}
