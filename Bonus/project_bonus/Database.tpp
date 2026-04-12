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

    DBEntry entry;
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
    std::size_t index;
    bool found = key1Tree.retrieve(key, index);

    if (!found) found = key2Tree.retrieve(key, index);

    if (!found) return false;

    DBEntry removedEntry = entries.getEntry(index);
    std::size_t lastIndex = entries.getLength() - 1;

    //remove keys for the entry being deleted
    key1Tree.remove(removedEntry.key1);
    key2Tree.remove(removedEntry.key2);

    //if not removing the last item, move last into this spot
    if (index != lastIndex) {
        DBEntry lastEntry = entries.getEntry(lastIndex);

        entries.setEntry(index, lastEntry);

        //update both trees for moved item
        key1Tree.remove(lastEntry.key1);
        key2Tree.remove(lastEntry.key2);
        key1Tree.insert(lastEntry.key1, index);
        key2Tree.insert(lastEntry.key2, index);
    }

    entries.remove(lastIndex);
    return true;
}

template <typename T>
void Database<T>::clear() {
    // TODO
    entries.clear();
    key1Tree.destroy();
    key2Tree.destroy();
}

template <typename T>
T Database<T>::getValue(const std::string& key) const {
    // TODO
    std::size_t index;
    bool found = key1Tree.retrieve(key, index);

    if (!found) found = key2Tree.retrieve(key, index);

    if (!found) throw std::out_of_range("Key not found in database");
    
    return entries.getEntry(index).value;
}

template <typename T>
bool Database<T>::contains(const std::string& key) const {
    // TODO
    std::size_t index;
    return key1Tree.retrieve(key, index) || key2Tree.retrieve(key, index);
}
