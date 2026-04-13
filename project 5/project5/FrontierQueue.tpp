#include "FrontierQueue.hpp"

template <typename T>
State<T> FrontierQueue<T>::pop() {
  //TODO: implement this the same way we implemented pop in the heap lecture. Compare states using getFCost.
  State<T> result = queue.front();

  queue[0] = queue.back();
  queue.pop_back();

  std::size_t i = 0;
  while (!queue.empty()) {
    std::size_t left = 2 * i +1;
    std::size_t right = 2 * i +2;
    std::size_t smallest = i;

    if (left < queue.size() && queue[left].getFCost()) {
      smallest = left;
    }

    if (right < queue.size() && queue[right].getFCost() < queue[smallest].getFCost()){
      smallest = right;
    }

    if (smallest == i) {
      break;
    }

    std::swap(queue[i], queue[smallest]);
    i = smallest;
  }


  return result;
}

template <typename T>
void FrontierQueue<T>::push(const T &p, std::size_t cost, std::size_t heur) {

  //TODO: implement this the same way we implemented push in the heap lecture.

}

template <typename T>
bool FrontierQueue<T>::empty() const {

  //TODO

  return true;
}

template <typename T> 
bool FrontierQueue<T>::contains(const T &p) const {

  //TODO

  return false;

}

template <typename T>
void FrontierQueue<T>::replaceif(const T &p, std::size_t cost) {

  //TODO

}


