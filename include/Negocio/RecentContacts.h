#ifndef RECENTCONTACTS_H
#define RECENTCONTACTS_H
#include <deque>
#include <vector>
#include <algorithm>

class RecentContacts {
private:
    std::deque<size_t> recents;
    static const size_t MAX = 20;
public:
    void add(size_t index);
    std::vector<size_t> getAll() const;
};
#endif // RECENTCONTACTS_H
