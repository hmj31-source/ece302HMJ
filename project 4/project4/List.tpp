#include "List.hpp"
//resize private var
template <typename T>
void List<T>::resize(std::size_t new_capacity)
{
  //declare new data list
  T* new_data = new T[new_capacity];

  //iterate over the length
  for (std::size_t i =0; i < length; ++i) {
    new_data[i] = data[i];
  }

  //delete old data list
  delete[] data;
  //set the data pointer to new_data
  data = new_data;
  //increase capacity
  capacity = new_capacity;
}

template <typename T>
List<T>::List()
{
  //TODO
  //set default capacity
  capacity = 4;
  //enpty constructor so length 0
  lenght =0;
  //create new list
  data = new T[capacity];
}

template <typename T>
List<T>::~List()
{
  //TODO
  //delete data
  delete[] data;
}

template <typename T>
List<T>::List(const List<T>& x)
{
  //TODO
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  //TODO
  return *this;
}

template <typename T>
void List<T>::swap(List<T>& x) 
{
  //TODO
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
