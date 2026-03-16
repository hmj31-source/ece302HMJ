#include "SortedList.hpp"
#include <stdexcept>

template <typename T>
SortedList<T>::SortedList()
{
  // base constructor gets called automatically
}

template <typename T>
SortedList<T>::SortedList(List<T> unsorted_list) 
{
  // TODO
  //copy over each element from the unsorted list
  for (std::size_t i =0; i <unsorted_list.getLength(); ++i) {
    insert(unsorted_list.getEntry(i));
  }

}

template <typename T>
SortedList<T>::SortedList(const SortedList<T> & x):
  List<T>(x)
{
}

template <typename T>
SortedList<T>& SortedList<T>::operator=(SortedList<T> x)
{
  List<T>::operator=(x);
  return *this;
}

template <typename T>
SortedList<T>::~SortedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedList<T>::isEmpty() const noexcept
{
  return List<T>::isEmpty();
}

template <typename T>
std::size_t SortedList<T>::getLength() const noexcept
{
  return List<T>::getLength();
}

template <typename T>
void SortedList<T>::insert(const T& item)
{
  // TODO
  std::size_t len = List<T>::getLength();
  std::size_t pos = 0;
  // Find the first position where item is <= the existing entry
  while (pos < len && List<T>::getEntry(pos) < item) {
    ++pos;
  }
  List<T>::insert(pos, item);
}

template <typename T>
void SortedList<T>::remove(const T& item)
{  
  // TODO
  std::size_t pos = getPosition(item); // throws std::invalid_argument if not found
  List<T>::remove(pos);
}

template <typename T>
void SortedList<T>::removeAt(std::size_t position)
{  
  // TODO
  List<T>::remove(position); // throws std::out_of_range if invalid
}

template <typename T>
void SortedList<T>::clear()
{
  List<T>::clear();
}

template <typename T>
T SortedList<T>::getEntry(std::size_t position) const
{
  return List<T>::getEntry(position);
}

template <typename T>
std::size_t SortedList<T>::getPosition(const T& item)
{
  // TODO
  std::size_t len = List<T>::getLength();
  for (std::size_t i = 0; i < len; ++i) {
    if (List<T>::getEntry(i) == item) {
      return i;
    }
  }
  throw std::invalid_argument("getPosition: item not found");
}
