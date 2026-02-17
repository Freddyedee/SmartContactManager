#include "RecentContacts.h"

void RecentContacts::add(int id) {
    // Buscar si el ID ya está en la lista para no duplicarlo
    auto it = std::find(recents.begin(), recents.end(), id);

    // Si existe, lo borramos de su posición actual
    if (it != recents.end()) {
        recents.erase(it);
    }

    // Lo insertamos al frente (el más reciente)
    recents.push_front(id);

    // Mantenemos el tamaño máximo
    if (recents.size() > MAX) {
        recents.pop_back();
    }
}

std::vector<int> RecentContacts::getAll() const {
    // Convertimos la deque a vector para retornarlo
    return std::vector<int>(recents.begin(), recents.end());
}
