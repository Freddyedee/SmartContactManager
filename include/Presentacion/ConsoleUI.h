#ifndef CONSOLEUI_H
#define CONSOLEUI_H
#include "ContactManager.h"
#include <string>

class ConsoleUI {
private:
    ContactManager* manager;

    void showMainMenu() const;
    void handleCreate();
    void handleUpdate();
    void handleDelete();
    void handleSearchByName();
    void handleSearchByTel();
    void handleSearchByEmail();
    void handleShowRecents();
    void handleExportCSV();
    void showContact(const Contacto& c, bool withIndex = false, size_t index = 0) const;
    void showContacts(const std::vector<Contacto>& contacts, bool withIndex = false) const;
    std::string readNonEmptyString(const std::string& prompt) const;
    size_t readIndex(const std::string& prompt, size_t max) const;

public:
    explicit ConsoleUI(ContactManager* mgr);
    void run();
};
#endif // CONSOLEUI_H
