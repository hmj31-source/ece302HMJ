#include "List.hpp"

template <typename T>
List<T>::List()
{
  //TODO
  //non specific intialization values
  capacity = 4;
  itemCount = 0;
  items = new T[capacity];
}

template <typename T>
List<T>::~List()
{
  //TODO
  //delete items in the list
  delete[] items;
}

template <typename T>
List<T>::List(const List<T>& x)
{
  //TODO
  //create list off of a vector using x's variables
  capacity = x.capacity;
  itemCount = x.itemCount;
  items = new T[capacity];

  //copy items over
  for (std::size_t i = 0; i < itemCount; i++){
    items[i] = x.items[i];
  }
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  //TODO
  //swap function
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List<T>& x) 
{
  //TODO
  //copy over the variables
  std::swap(items, x.items);
  std::swap(itemCount, x.itemCount);
  std::swap(capacity, x.capacity);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  //TODO
  return true;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  //TODO
  return 0;
}

template <typename T>
void List<T>::insert(std::size_t position, const T& item)
{
  //TODO
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  //TODO
}

template <typename T>
void List<T>::clear()
{
  //TODO
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  //TODO
  return T();
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
}
