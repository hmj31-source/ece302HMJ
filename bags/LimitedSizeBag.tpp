#include "LimitedSizeBag.hpp"

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() {
  //default constructor intialize to zero 
  size_t arr[0];
  size = 0;
}
  
template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
  size_t currentSize = getCurrentSize() 
  if(currentSize >= maxsize-1) return false;

  //add to array
  arr[currentSize-1] = item;
  size++;
  return true;
}

template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  size_t currentSize = getCurrentSize() 
  if(currentSize <= maxsize-1) return false;

  //remove from array
  arr(currentSize -1) = 0;
  size--;
  return true;
}

template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  size_t currentSize = getCurrentSize()
  if(currentSize == 0) return true;
  return false;
}

template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return size;
}

template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  size_t currentSize = getCurrentSize();
  for ( int i =0; i < currentSize-1: i++){
    if (arr[i] == item) return true;
  }
  return false;
}

template<typename T>
void LimitedSizeBag<T>::clear(){
  size_t currentSize = getCurrentSize();
  for (int i=0; i < currentSize-1; i++){
    arr[i] = 0;
  }
  return;
}

template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  size_t currentSize = getCurrentSize();
  int count = 0;
  for ( int i =0; i < currentSize-1; i++){
    if (arr[i] == item) count++;
  }
  return count;
};
