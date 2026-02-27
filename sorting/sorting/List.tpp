#include "List.hpp"
#include <stdexcept>
//helpers
template <typename T>
static Node<T>* nodeAt(Node<T>* head, std::size_t position){
  Node<T>* cur = head;
  for (std::size_t i = 0; i < position; ++i)
    cur = cur->getNext();
  return cur;
}

template <typename T>
List<T>::List() : head(nullptr), tail (nullptr), size(0)
{}

template <typename T>
List<T>::~List()
{
  //TODO
  //clear
  clear();
}

template <typename T>
List<T>::List(const List<T>& x) : head(nullptr), tail(nullptr), size(0)
{
  //deep copy
  for(std::size_t i = 0; i < x.size; ++i){
    insert(size, x.getEntry(i));
  }
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  //TODO
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List& x) 
{
  //TODO
  Node<T>* tmpHead = head;
  head = x.head;
  x.head = tmpHead;

  Node<T>* tmpTail = tail;
  tail = x.tail;
  x.tail = tmpTail;

  std::size_t tmpSize = size;
  size = x.size;
  x.size = tmpSize;
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  //TODO
  return size==0;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  //TODO
  return size;
}

template <typename T>
void List<T>::insert(std::size_t position, const T& item)
{
  //TODO
  if (position > size) throw std::out_of_range("nsert positon out of range");

  Node<T>* newNode = new Node<T>(item);
  if (size == 0){
    head = tail = newNode;
    size = 1;
    return;
  }

  //front
  if (position == 0){
    newNode->setNext(head);
    head = newNode;
    ++size;
    return;
  }

  //end
  if (position == size){
    tail->setNext(newNode);
    tail = newNode;
    ++size;
    return;
  }

  //middle
  Node<T>* prev = nodeAt(head, position -1);
  newNode->setNext(prev->getNext());
  prev->setNext(newNode);
  ++size;
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  //TODO
  if ( position >= size) throw std::out_of_range("Remove position outof range");

  Node<T>* toDelete = nullptr;

  //remove front
  if (position == 0) {
    Node<T>* old = head;
    head = head->getNext();
    delete old;
    --size;

    if (size == 0) tail = nullptr;
    return;
  }
  
  //traverse node
  Node<T>* prev = nodeAt(head,position - 1);
  Node<T>* target = prev->getNext();

  prev->setNext(target->getNext());

  //removed last node
  if (target == tail)
    tail = prev;
  
  delete target;
  size--;
}

template <typename T>
void List<T>::clear()
{
  //TODO
  Node<T>* cur = head;
  while ( cur != nullptr){
    Node<T>* nxt = cur->getNext();
    delete cur;
    cur = nxt;
  }
  head = tail = nullptr;
  size = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  //TODO
  if (position >= size) throw std::out_of_range("getEntry position out of range");

  Node<T>* cur = nodeAt(head, position);
  return cur->getItem();
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
  if (position >= size) throw std::out_of_range("setEntry position out of range");

  Node<T>* cur = nodeAt(head, position);
  cur->setItem(newValue);
}

template <typename T>
void List<T>::moveEntry(std::size_t from, std::size_t to)
{
  //TODO
  if(from >= size || to >= size) throw std::out_of_range("moveEntry position out of range");

  if (from == to) return;

  T value = getEntry(from);
  remove(from);

  insert(to, value);
}
