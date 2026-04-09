#include "Database.hpp"
#include <stdexcept>

template <typename T>
Database<T>::Database() {
    // TODO
    //leave blank
}

template <typename T>
bool Database<T>::isEmpty() const {
    // TODO
    return entries.isEmpty();
}

template <typename T>
std::size_t Database<T>::getNumberOfEntries() const {
    // TODO
    return entries.getLength();
}

template <typename T>
bool Database<T>::add(std::string key1, std::string key2, T item) {
    // TODO
    if (contains(key1) || contains(key2)) return false;

    DbEntry entry;
    entry.key1 = key1;
    entry.key2 = key2;
    entry.value = item;

    std::size_t index = entries.getLength();
    entries.insert(index,entry);

    key1Tree.insert(key1,index);
    key2Tree.insert(key2, index);

    return true;
}

template <typename T>
bool Database<T>::remove(const std::string& key) {
    // TODO
    return false;
}

template <typename T>
void Database<T>::clear() {
    // TODO
}

template <typename T>
T Database<T>::getValue(const std::string& key) const {
    // TODO
    return T();
}

template <typename T>
bool Database<T>::contains(const std::string& key) const {
    // TODO
    return false;
}
