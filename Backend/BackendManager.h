#ifndef BACKENDMANAGER_H
#define BACKENDMANAGER_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QDateTime>


#include "Negocio/ContactManager.h"


class BackendManager : public QObject{

    Q_OBJECT

public:
    explicit BackendManager(QObject* parent = nullptr);

    //CRUD


    Q_INVOKABLE bool addContact(const QString& nombre,
                                const QString& telefono,
                                const QString& email);

    Q_INVOKABLE QVariantList getContacts();

    Q_INVOKABLE bool updateContact(int id,
                                   const QString& nombre,
                                   const QString& telefono,
                                   const QString& email);

    Q_INVOKABLE bool deleteContact(int id);

    // Consultas
    Q_INVOKABLE QVariantList getAllContacts();
    Q_INVOKABLE QVariantList searchByName(const QString& prefix);
    Q_INVOKABLE QVariantList getRecentContacts();
    Q_INVOKABLE QVariantMap searchByTelOrEmail(const QString& value);



    // Exportación
    Q_INVOKABLE void exportCSV(const QString& path);

private:
    ContactManager manager;

    QVariantMap contactoToMap(const Contacto& c);
    void logAction(const QString& action, const Contacto& c);

};

#endif // BACKENDMANAGER_H
