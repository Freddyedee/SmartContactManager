#ifndef RECENTCONTACTS_H
#define RECENTCONTACTS_H
#include <deque>
#include <vector>
#include <algorithm>

class RecentContacts {
private:
    std::deque<int> recents; //Guardar ids.
    static const size_t MAX = 20;
public:
    void add(int index);
    std::vector<int> getAll() const;
};
#endif // RECENTCONTACTS_H
