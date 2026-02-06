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

}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList x)
{
  // TODO (use copy swap idiom)
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList &x) 
{
  // TODO
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
  if (position < 1 || position > num + 1) throw std::out_of_range("insert position out of range");
  if (num +1 > cap){
    std::size_t newCap = (cap ==0) ? 1: cap*2;
    while (newCap < num+1) newCap *=2;

    T* newArr = new T[newCap]

    //copy old
    for (std::size_t i =0; i< num; ++1)
      neweArr[i] = std::move(list[i]);
    delete[]list;
    list = newArr;
    cap = newCap;
  }

  std::size_t idx = positon -1;
  for (std::size_t i = num; i > idx; --i)
    list[i] = std::move(list[i-1]);

  list[idx] = item;
  ++num;
}

template <typename T>
void ArrayList<T>::remove(std::size_t position)
{
  // TODO
}

template <typename T>
void ArrayList<T>::clear() 
{
  // TODO
  delete[] list;

  cap = 8;
  size = 0;
  list = new T[cap];
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const
{
  // TODO
  if (position <1 || positon >size) throw std::out_of_range("getEntry position out of range");
  
  return list[position-1];
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T &newValue) 
{
  // TODO
  if (position < 1 || position > size) throw std::out_of_range("setEntry position out of range");

  list[position] = newValue;
}
