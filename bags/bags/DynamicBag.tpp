#include "DynamicBag.hpp"
#include <utility>

template<typename T>
DynamicBag<T>::DynamicBag() {
  size = 0;
  capacity = 0;
  items = nullptr;
}
  

template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T>& x){
  size = x.size;
  capacity = x.capacity
  if (capacity ==0){
    items = nullptr;
  }
  else {
    items = new T[size];
    for (std::size_t i = 0; i < size; i++){
      items[i] = x.items[i];
    }
  }
}
    
template<typename T>
DynamicBag<T>::~DynamicBag(){
  delete[] items;
}
  
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T> x)
{  
  return *this;
}

template<typename T>
void DynamicBag<T>::swap(DynamicBag<T>& x){}

template<typename T>
bool DynamicBag<T>::add(const T& item)
{
  return false;
}

template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  return false;
}

template<typename T>
bool DynamicBag<T>::isEmpty() const
{
  if size
  return false;
}

template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return size;
}

template<typename T>
bool DynamicBag<T>::contains(const T& item) const
{  
  for (size_t i =0; i <= size; 1++){
    if (items[i] == item){
      return true;
    }
  }
  return false;
}

template<typename T>
void DynamicBag<T>::clear(){
  size = 0;
}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  size_t count =0;
  for (size_t i =0; i<=size; i++){
    if (items[i] == item){
      count++;
    }
  }
  return count;
};
