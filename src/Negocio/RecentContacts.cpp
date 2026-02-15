#include "RecentContacts.h"

void RecentContacts::add(size_t index) {
    auto it = std::find(recents.begin(), recents.end(), index);
    if (it != recents.end()) recents.erase(it);
    recents.push_front(index);
    if (recents.size() > MAX) recents.pop_back();
}

std::vector<size_t> RecentContacts::getAll() const {
    return std::vector<size_t>(recents.begin(), recents.end());
}
