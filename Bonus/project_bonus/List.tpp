#include "List.hpp"

template <typename T>
List<T>::List()
{
  //TODO
  //non specific intialization values
  capacity = 4;
  itemCount = 0;
  items = new T[capacity];
}

template <typename T>
List<T>::~List()
{
  //TODO
  //delete items in the list
  delete[] items;
}

template <typename T>
List<T>::List(const List<T>& x)
{
  //TODO
  //create list off of a vector using x's variables
  capacity = x.capacity;
  itemCount = x.itemCount;
  items = new T[capacity];

  //copy items over
  for (std::size_t i = 0; i < itemCount; i++){
    items[i] = x.items[i];
  }
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  //TODO
  //swap function
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List<T>& x) 
{
  //TODO
  //copy over the variables
  std::swap(items, x.items);
  std::swap(itemCount, x.itemCount);
  std::swap(capacity, x.capacity);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  //TODO
  //return wheter the itemCount is 0 or not
  return itemCount == 0;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  //TODO
  //return the itemcount
  return itemCount;
}

//implement private method resize
template <typename T>
void List<T>::resize(std::size_t newCapacity)
{
  //chech if the userdefined newcapacity is less the itemcount
  if (newCapacity < itemCount){
    //if less set the newcap to itemcount
    newCapacity = itemCount;
  }

  //declare new items list
  T* newItems = new T[newCapacity];
  //copy the items over
  for (std::size_t i = 0; i < itemCOunt; i++) {
    newItems[i] = items[i];
  }

  //delete old list
  delete[] items;
  //set items to new items
  items = newItems;
  //set capacity to new capacity
  capacity = newCapacity;
}


template <typename T>
void List<T>::insert(std::size_t position, const T& item)
{
  //TODO
  //bounds check
  if (position > itemCount) throw std::out_of_range("List insert position out of range");

  //capacity check and resize
  if (itemCount == capacity) resize(capacity * 2);

  //move items over
  for (std::size_t i = itemCount; i > position; i--){
    items[i] = items[i-1];
  }

  //insert hte item
  itesm[position] = item;
  itemCount++;
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  //TODO
  //bounds check
  if (position >= itemCOunt) throw std::out_of_range("List remove position out of range");

  //move items over 
  for (std::size_t i = position; i + 1 < itemCOunt; i++) {
    items[i] = items[i+1];
  }
  //reduce item count
  itemCount--;

  //reduce capacity
  if (capcity > 4 && itemCOunt <= capcity / 4) {
    resize(capacity/2);
  }
}

template <typename T>
void List<T>::clear()
{
  //TODO
  //delete the items
  delete[] items;
  //set capcity and itemcount and items to basic constuctor settings
  capacity = 4;
  itemCount = 0;
  items = new T[capacity];
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  //TODO
  //bounds check
  if (position >= itemCount) throw std::out_of_range("List getEntry position out of range");
  
  //return item at the postion
  return items[position];
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
  //bounds check
  if (position >= itemCount) throw std::out_of_range("List setEntry position out of range");

  //set position to newValue
  items[position] = newValue;
}
