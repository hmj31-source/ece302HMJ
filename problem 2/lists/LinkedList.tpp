#include "LinkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  // TODO
  headPtr = nullptr;
  itemCount = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  // TODO
  Node<T>* cur = headPtr;

  while (cur != nullptr){
    Node<T>* next = cur->getNext();
    delete cur;
    cur = next;
  }

  headPtr=nullptr;
  itemCount =0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &x)
{
  // TODO
  if (x.headPtr == nullptr){
    headPtr = nullptr;
    itemCount = 0;
  }
  else {
    headPtr = new Node<T>(x.headPtr->getItem());
    itemCount = x.itemCount;

    Node<T>* newCur = headPtr;
    Node<T>* origCur = x.headPtr->getNext();

    while (origCur != nullptr) {
      Node<T>* newNode = new Node<T>(origCur->getItem());
      newCur->setNext(newNode);

      newCur = newCur->getNext();
      origCur = origCur->getNext();
    }
  }
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> x)
{
  // TODO (use copy swap idiom)
  swap(x);
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList &x)
{
  // TODO
  std::swap(headPtr, x.headPtr);
  std::swap(itemCount, x.itemCount);
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  // TODO
  if (itemCount == 0) return true;
  return false;
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  // TODO
  return itemCount;
}

template <typename T>
void LinkedList<T>::insert(std::size_t position, const T &item)
{
  // TODO
  if (position < 1 || position > itemCount +1) throw std::out_of_range("insert out of range");

  Node<T>* newNode = new Node<T>(item);

  if (position == 1){
    newNode->setNext(headPtr);
    headPtr = newNode;
  }
  else{
    Node<T>* prev = headPtr;

    for (size_t i=1; i< position -1; ++i)
      prev = prev->getNext();

    newNode->setNext(prev->getNext());
    prev->setNext(newNode);
  }
  ++itemCount;
}

template <typename T>
void LinkedList<T>::remove(std::size_t position)
{
  // TODO
  if (position < 1 || position > itemCount) throw std::out_of_range("remove out of range");

  Node<T>* toDelete = nullptr;

  if (position == 1){
    toDelete = headPtr;
    headPtr = headPtr->getNext();
  }
  else{
    Node<T>* prev = headPtr;

    for (size_t i=1; i < position - 1; ++i)
      prev = prev->getNext();
    
    toDelete = prev->getNext();
    prev->setNext(toDelete->getNext());
  }
  delete toDelete;
  --itemCount;
}

template <typename T>
void LinkedList<T>::clear()
{
  // TODO
  Node<T>* cur = headPtr;

  while (cur != nullptr) {
    Node<T>* next = cur->getNext();
    delete cur;
    cur = next;
  }
  headPtr = nullptr;
  itemCount = 0;
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  // TODO
  if (position < 1 || position > itemCount)
    throw std::out_of_range("getEntry position out of range");

  Node<T>* cur = headPtr;

  for (std::size_t i = 1; i <position; ++i)
    cur = cur->getNext();

  return cur->getItem();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T &newValue)
{
  // TODO
  if (position < 1 || position > itemCount) throw std::out_of_range("setEntry position out of range");

  Node<T>* cur = headPtr; 

  for (std::size_t i = 1; i < position; ++i)
    cur = cur->getNext();

  cur->setItem(newValue);
}
