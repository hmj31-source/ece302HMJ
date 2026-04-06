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
  //empty constructor so length 0
  length = 0;
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
  //set x variable to this lists implementation of varibles
  capacity = x.capacity;
  length = x.length;
  //new variable to copy data over
  data = new T[capacity];

  //iterate over length and copy data
  for (std::size_t i = 0; i < length; ++i){
    data[i] = x.data[i];
  }
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  //TODO
  //assign the x to this list
  swap(x);
  //return this list 
  return *this;
}

template <typename T>
void List<T>::swap(List<T>& x) 
{
  //TODO
  //call std swap to swap all the data and variable
  std::swap(data, x.data);
  std::swap(length, x.length);
  std::swap(capacity, x.capacity);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  //TODO
  //if length = 0 then return 0
  return length==0;
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
  //bounds check
  if (position > length) throw std::out_of_range("Insert position out of range");

  //resize if needed
  if (length == capacity) resize(capacity*2);

  //interate through each and move over one after the insert position
  for (std::size_t i = length; i > position; --i){
    data[i] = data[i-1];
  }
  //insert and increase length
  data[position] = item;
  ++length;
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  //TODO
  //bounds check
  if (position >= length) throw std::out_of_range("remove position out of range");
  
  //iterate thorugh each to shift left 
  for (std::size_t i = position; i + 1 < length; ++i){
    data[i] = data[i+1];
  }
  //decraese lenght
  --length;
}

template <typename T>
void List<T>::clear()
{
  //TODO
  //clear by setting length to 0
  length = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  //TODO
  //bounds check
  if (position >= length) throw std::out_of_range("getEntry position out of range");

  //return the data at this location
  return data[position];
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
  //bounds check a
  if (position >= length) throw std::out_of_range("setEntry position out of range");

  //insert at that position
  data[position] = newValue;
}
