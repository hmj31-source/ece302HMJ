#include "ArrayList.hpp"

template <typename T>
ArrayList<T>::ArrayList()
{
  // TODO
  cap=0;
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
  cap = x.cap;

  if (cap ==0) list = nullptr;
  else{
    list = new T[cap];

    for (std::size_t i = 0; i < size; ++i)
      list[i] = x.list[i];
  }
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
  std::swap(cap, x.cap);
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
  // TODO
  if (position < 1 || position > size + 1) throw std::out_of_range("insert position out of range");
  if (size +1 > cap){
    std::size_t newCap = (cap ==0) ? 1: cap*2;
    while (newCap < size+1) newCap *=2;

    T* newArr = new T[newCap];

    //copy old
    for (std::size_t i =0; i< size; ++i)
      newArr[i] = std::move(list[i]);
    delete[]list;
    list = newArr;
    cap = newCap;
  }

  std::size_t idx = position -1;
  for (std::size_t i = size; i > idx; --i)
    list[i] = std::move(list[i-1]);

  list[idx] = item;
  ++size;
}

template <typename T>
void ArrayList<T>::remove(std::size_t position)
{
  // TODO
  if (position < 1 || position > size) throw std::out_of_range("remove position out of range");

  std::size_t idx = position -1;

  for (std::size_t i = idx; i + 1 < size; ++i)
    list[i] = std::move(list[i+1]);

  --size;
}

template <typename T>
void ArrayList<T>::clear() 
{
  // TODO
  delete[] list;
  list = nullptr;

  cap = 0;
  size = 0;
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const
{
  // TODO
  if (position <1 || position >size) throw std::out_of_range("getEntry position out of range");
  
  return list[position-1];
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T &newValue) 
{
  // TODO
  if (position < 1 || position > size) throw std::out_of_range("setEntry position out of range");

  list[position-1] = newValue;
}
