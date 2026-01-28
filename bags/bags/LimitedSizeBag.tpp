#include "LimitedSizeBag.hpp"

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() {
  //default constructor intialize to zero 
  size = 0;
}
  
template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
  if(size >= maxsize) return false;

  //add to array
  items[size] = item;
  size++;
  return true;
}

template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  for(std::size_t i = 0; i < size; i++) {
  if(items[i] == item ){
    items[i] = items[size -1];
    items[size - 1] = T{};
    size--;
    return true;
  }
}
return false;
}

template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  return size == 0;
}

template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return size;
}

template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  for (std::size_t i =0; i < size; i++){
    if (items[i] == item) return true;
  }
  return false;
}

template<typename T>
void LimitedSizeBag<T>::clear(){
  for (std::size_t i=0; i < size; i++) items[i] = T{};
  size = 0;
}

template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t count = 0;
  for ( std::size_t i =0; i < size; i++){
    if (items[i] == item) count++;
  }
  return count;
}
