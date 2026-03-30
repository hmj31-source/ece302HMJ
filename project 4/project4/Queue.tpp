#include "Queue.hpp"

template <typename T, typename L>
void Queue<T,L>::enqueue(const T& item)
{
  // TODO
  internal_list.insert(internal_list.getLength(), item);
}

template <typename T, typename L>
void Queue<T,L>::dequeue()
{
  // TODO
  internal_list.remove(0);
}

template <typename T, typename L>
T Queue<T,L>::peekFront() const
{
  // TODO
  return internal_list.getEntry(0);
}

template <typename T, typename L>
bool Queue<T,L>::isEmpty() const
{
  // TODO
  return internal_list.isEmpty();
}

