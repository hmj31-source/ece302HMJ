#include "List.hpp"

template <typename T>
List<T>::List() : head(nullptr), length(0)
{
  //TODO
  //declare head nullptr and length 0
}

template <typename T>
List<T>::~List()
{
  //TODO
  //clear list
  clear();
}

template <typename T>
List<T>::List(const List<T>& x)
{
  //TODO
  //for length of x copy the entries to this array
  for (std::size_t i = 0; i < x.getLength(); ++i) {
    insert(i, x.getEntry(i));
  }
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  //TODO
  //swap with x
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List& x) 
{
  //TODO
  //swap each variable
  std::swap(head, x.head);
  std::swap(length, x.length);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  //TODO
  //return treu if length = 0
  return length ==0;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  //TODO
  return length;
}

template <typename T>
Node<T>* List<T>::getNodeAt(std::size_t position) const
{
  Node<T>* cur = head;
  for (std::size_t i = 0; i < position; ++1) {
    cur = cur->getNext();
  }
  return cur;
}

template <typename T>
void List<T>::insert(std::size_t position, const T& item)
{
  //TODO
  //bounds checking
  if (position > length) {
    throw std::out_of_range("insert position out of range");
  }
  //Declare new node
  Node<T>* newNode = new Node<T>(item);
  //if position = 0 new node next is the head and the new head is newnode
  if (position == 0){
    newNode->setNext(head);
    head = newNode;
  } else{ //if position is not 1 find the previous node 
    Node<T?* prev = getNodeAt(position -1);
    newNode->setNext(prev->getNext());
    prev->setNext(newNode);
  }
  //increase length
  ++length;
}


template <typename T>
void List<T>::remove(std::size_t position)
{
  //TODO
  //bounds check
  if (position >= length) {
    throw std::out_of_range("remove postition out of range");
  }
  //create a delete node
  Node<t>* toDelete;
  //if the postion is the head then set to delete
  if (position == head){
    toDelete = head;
    //new head is the next node
    head = head->getNext();
  } else { // if position isn't head
    //find hte prevous node
    Node<T>* prev = getNodeAt(position -1);
    //delete the next node 
    toDelete = prev->getNext();
    prev->setNext(toDelete->getNext());
  }
  //delete and decrimant lenght
  delete toDelete;
  --length;
}

template <typename T>
void List<T>::clear()
{
  //TODO
  //run while the head is not a nullptr
  while (head != nullptr) {
    //set the head to delete
    Node<T>* toDelete = head;
    //set next as teh head
    head = head->getNext();
    //delete previous head
    delete toDelete;
  }
  //once it finsihes length is 0
  length = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  //TODO
  //boudns check
  if (position >= length) {
    throw std::out_of_range("getEntry position out of range");
  }
  //use getNodeAt() function and get that item
  return getNodeAt(position)->getItem();
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
  //bounds check
  if (position >= length) {
    throw std::out_of_range("setEntry position out of range");
  }
  //use getNodeAt and set the item
  getNodeAt(position)->setItem(newValue);
}
