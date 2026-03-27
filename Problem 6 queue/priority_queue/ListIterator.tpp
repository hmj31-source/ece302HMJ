#include "ListIterator.hpp"

/* Change the second constructor argument to Node<T>* if using a linked implementation */
template <typename T>
inline ListIterator<T>::ListIterator(List<T> *listPtr, T *itemPtr) : listptr(listPtr), itemPtr(itemPtr)
{
    // TODO
    //done in the definition
}

template <typename T>
inline T ListIterator<T>::operator*() const
{
    // TODO
    return *itemPtr;
}

template <typename T>
inline ListIterator<T> ListIterator<T>::operator++()
{
    // TODO
    ++itemPtr;
    return *this;
}

template <typename T>
inline bool ListIterator<T>::operator==(const ListIterator<T> &rhs) const
{
    // TODO
    return (listptr == rhs.listptr) && (itemPtr == rhs.itemPtr);
}

template <typename T>
inline bool ListIterator<T>::operator!=(const ListIterator<T> &rhs) const
{
    // TODO
    return !(*this == rhs);
}