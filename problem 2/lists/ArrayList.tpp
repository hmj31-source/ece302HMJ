#include "ArrayList.hpp"

template <typename T>
ArrayList<T>::ArrayList()
{
  // TODO
  size=0;
  list = nullptr;
}

template <typename T>
ArrayList<T>::~ArrayList() 
{
  // TODO
  delete[] list;
  list = nullptr;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList &x) 
{
  // TODO
  size = x.size;
  list = (size > 0) ? new T[size] : nullptr;

  for (std::size_t i = 0; i < size; ++i)
    list[i] = x.list[i];
}
template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList x)
{
  // TODO (use copy swap idiom)
  swap(x);
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList &x) 
{
  // TODO
  std::swap(list, x.list);
  std::swap(size, x.size);
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept
{
  // TODO
  if (size == 0) return true;
  return false;
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept
{
  // TODO
  return size;
}

template <typename T>
void ArrayList<T>::insert(std::size_t position, const T &item)
{
  //TODO
  if (position > size) throw std::out_of_range("insert out of range");

  T* newArr = new T[size + 1];

  // copy before position
  for (std::size_t i = 0; i < position; ++i)
    newArr[i] = list[i];

  // insert item
  newArr[position] = item;

  // copy after position (shift right)
  for (std::size_t i = position; i < size; ++i)
    newArr[i + 1] = list[i];

  delete[] list;
  list = newArr;
  ++size;

}

template <typename T>
void ArrayList<T>::remove(std::size_t position)
{
  // TODO
  if (position >= size) throw std::out_of_range("remove out of range");

  T* newArr = (size > 1) ? new T[size - 1] : nullptr;

  // copy before position
  for (std::size_t i = 0; i < position; ++i)
    newArr[i] = list[i];

  // copy after position (shift left)
  for (std::size_t i = position + 1; i < size; ++i)
    newArr[i - 1] = list[i];

  delete[] list;
  list = newArr;
  --size;

}

template <typename T>
void ArrayList<T>::clear() 
{
  // TODO
  delete[] list;
  list = nullptr;

  size = 0;
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const
{
  // TODO
  if (position >= size) throw std::out_of_range("getEntry out of range");
  return list[position];

}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T &newValue) 
{
  // TODO
  if (position >= size) throw std::out_of_range("setEntry out of range");
  list[position] = newValue;
}
