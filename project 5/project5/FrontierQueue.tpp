#include "FrontierQueue.hpp"

template <typename T>
State<T> FrontierQueue<T>::pop() {
  //TODO: implement this the same way we implemented pop in the heap lecture. Compare states using getFCost.
  State<T> result = queue.front();

  queue[0] = queue.back();
  queue.pop_back();

  return result;
}

template <typename T>
void FrontierQueue<T>::push(const T &p, std::size_t cost, std::size_t heur) {
  //TODO: implement this the same way we implemented push in the heap lecture.
  queue.push_back(State<T>(p, cost, heur));

  std::size_t i = queue.size() - 1;
  while (i > 0) {
    std::size_t parent = (i-1) /2;

    if (queue[i].getFCost() < queue[parent].getFCost()) {
      std::swap(queue[i], queue[parent]);
      i = parent;
    } else {
      break;
    }
  }
}

template <typename T>
bool FrontierQueue<T>::empty() const {
  //TODO
  return queue.empty();
}

template <typename T> 
bool FrontierQueue<T>::contains(const T &p) const {
  //TODO
  for (std::size_t i = 0; i < queue.size(); ++i) {
    if (queue[i].getValue() == p){
      return true;
    }
  }
  return false;
}

template <typename T>
void FrontierQueue<T>::replaceif(const T &p, std::size_t cost) {
  //TODO
  for (std::size_t i = 0; i < queue.size(); ++i) {
    if (queue[i].getValue() == p){
      if (cost < queue[i].getPathCost()) {
        queue[i].updatePathCost(cost);

        while (i > 0) {
          std::size_t parent = (i - 1) /2;
          if (queue[i].getFCost() < queue[parent].getFCost()) {
            std::swap(queue[i], queue[parent]);i = parent;
          } else {
            break;
          }
        }
      }
      return;
    }
  }
}


