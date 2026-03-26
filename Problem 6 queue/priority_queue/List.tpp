#include "List.hpp"

template <typename T>
List<T>::List() : data(nullptr), length(0), capacity(0)
{
  //TODO
  //done in statement
}

template <typename T>
List<T>::~List()
{
  //TODO
  //delete the data
  delete[] data;
}

template <typename T>
List<T>::List(const List<T>& x) :data(nullptr). length(x.length), capacity(x.capacity)
{
  //TODO
  //bounds check
  if (capacity > 0) {
    //new data 
    data = new T[capacity];
    //iterate over length and copy the data
    for (std::size_t i = 0; i < length; ++i){
      data[i] = x.data[i];
    }
  }
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  //TODO
  //swap
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List<T>& x) 
{
  //TODO
  //swap all data
  std::swap(data, x.data);
  std::swap(length, x.length);
  std::swap(capacity, x.cpacity);
}

template <typename T>
void List<T>::reserve(std::size_t newCapacity)
{
  //reserve space
  if (newCapacity <= capacity) {
    return;
  }

  T* newData = new T[newCapacity];
  for (std::size_t i = 0; i < length; ++1) {
    newData[i] = data[i];
  }

  delete[] data;
  data = newData;
  capacity = newCapacity;
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  //TODO
  return length == 0;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  //TODO
  return length;
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

template <typename T>
ListIterator<T> List<T>::begin() 
{
  // TODO
  return ListIterator<T>(this, data);
}

template <typename T>
ListIterator<T> List<T>::end() 
{
  // TODO
  return ListIterator<T>(this, data + length);
}