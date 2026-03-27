#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "List.hpp"
#include "SortedList.hpp"
#include "PriorityQueue.hpp"

typedef SortedList< int, List<int> > SortedListType;
typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

/* Provided test cases */
TEST_CASE("Priority: Testing List Iterator", "[iterator]") {
  // empty list
  List<int> lst;
  REQUIRE(lst.begin() == lst.end());

  // loop tests
  List<int> lst2;
  int size = 100;
  for (int i=0; i<size; i++) {
    lst2.insert(i,i+10);
  }

  // increment and dereference operators
  ListIterator<int> it = lst2.begin();
  int i=0;
  bool deref_increment_match = true;
  while (it != lst2.end()) {
    if(*it != i+10) {
      deref_increment_match = false;
      break;
    }
    ++it;
    i++;
  }
  REQUIRE(deref_increment_match);

  // range based loop
  bool range_based_match = true;
  int j=0;
  for (int item : lst2) {
    if(item != j+10) {
      range_based_match = false;
      break;
    }
    j++;
  }
  REQUIRE(range_based_match);

}

TEST_CASE("Priority: Testing Sorted List", "[sorted list]") {
  SortedList< int, List<int> >  sort;

  REQUIRE(sort.isEmpty());
  REQUIRE(sort.getLength() == 0);

  sort.insert(1);
  REQUIRE_FALSE(sort.isEmpty());
  REQUIRE(sort.getLength() == 1);
  sort.insert(2);
  REQUIRE(sort.getLength() == 2);
  sort.insert(8);
  REQUIRE(sort.getLength() == 3);
  sort.insert(6);
  REQUIRE(sort.getLength() == 4);
  sort.insert(9);
  REQUIRE(sort.getLength() == 5);
  sort.insert(0);
  REQUIRE(sort.getLength() == 6);

  REQUIRE(sort.getEntry(0) == 0);
  REQUIRE(sort.getPosition(0) == 0);
  REQUIRE(sort.getEntry(1) == 1);
  REQUIRE(sort.getPosition(1) == 1);
  REQUIRE(sort.getEntry(2) == 2);
  REQUIRE(sort.getPosition(2) == 2);
  REQUIRE(sort.getEntry(3) == 6);
  REQUIRE(sort.getPosition(6) == 3);
  REQUIRE(sort.getEntry(4) == 8);
  REQUIRE(sort.getPosition(8) == 4);
  REQUIRE(sort.getEntry(5) == 9);
  REQUIRE(sort.getPosition(9) == 5);
  
  sort.remove(0);
  REQUIRE(sort.getEntry(0) == 1);
  REQUIRE(sort.getLength() == 5);

  sort.remove(1);
  REQUIRE(sort.getEntry(0) == 2);
  REQUIRE(sort.getLength() == 4);

  sort.remove(9);
  REQUIRE(sort.getEntry(0) == 2);
  REQUIRE(sort.getLength() == 3);

  sort.removeAt(2);
  REQUIRE(sort.getEntry(0) == 2);
  REQUIRE(sort.getLength() == 2);

  sort.removeAt(0);
  REQUIRE(sort.getEntry(0) == 6);
  REQUIRE(sort.getLength() == 1);

  sort.removeAt(0);
  REQUIRE(sort.getLength() == 0);
  REQUIRE(sort.isEmpty());
  
}


TEST_CASE("Priority: Testing Priority Queue Add and isEmpty", "[priority queue]") {
  PriorityQueueType pq;

  REQUIRE(pq.isEmpty());

  pq.add(3);

  REQUIRE_FALSE(pq.isEmpty());
}

/* Your test cases here */
TEST_CASE("Priority: Testing List basic operations", "[list]") {
  List<int> lst;

  REQUIRE(lst.isEmpty());
  REQUIRE(lst.getLength() == 0);

  lst.insert(0, 10);
  REQUIRE_FALSE(lst.isEmpty());
  REQUIRE(lst.getLength() == 1);
  REQUIRE(lst.getEntry(0) == 10);

  lst.insert(1, 30);   // append
  lst.insert(1, 20);   // middle insert

  REQUIRE(lst.getLength() == 3);
  REQUIRE(lst.getEntry(0) == 10);
  REQUIRE(lst.getEntry(1) == 20);
  REQUIRE(lst.getEntry(2) == 30);

  lst.setEntry(1, 25);
  REQUIRE(lst.getEntry(1) == 25);

  lst.remove(1);
  REQUIRE(lst.getLength() == 2);
  REQUIRE(lst.getEntry(0) == 10);
  REQUIRE(lst.getEntry(1) == 30);

  lst.clear();
  REQUIRE(lst.isEmpty());
  REQUIRE(lst.getLength() == 0);
}

TEST_CASE("Priority: Testing List insert at front middle back", "[list]") {
  List<int> lst;

  lst.insert(0, 2); // [2]
  lst.insert(0, 1); // [1,2]
  lst.insert(2, 4); // [1,2,4]
  lst.insert(2, 3); // [1,2,3,4]

  REQUIRE(lst.getLength() == 4);
  REQUIRE(lst.getEntry(0) == 1);
  REQUIRE(lst.getEntry(1) == 2);
  REQUIRE(lst.getEntry(2) == 3);
  REQUIRE(lst.getEntry(3) == 4);
}

TEST_CASE("Priority: Testing List copy constructor", "[list]") {
  List<int> a;
  a.insert(0, 10);
  a.insert(1, 20);
  a.insert(2, 30);

  List<int> b(a);

  REQUIRE(b.getLength() == 3);
  REQUIRE(b.getEntry(0) == 10);
  REQUIRE(b.getEntry(1) == 20);
  REQUIRE(b.getEntry(2) == 30);

  a.setEntry(1, 99);

  // ensure deep copy
  REQUIRE(a.getEntry(1) == 99);
  REQUIRE(b.getEntry(1) == 20);
}

TEST_CASE("Priority: Testing List assignment operator", "[list]") {
  List<int> a;
  a.insert(0, 1);
  a.insert(1, 2);
  a.insert(2, 3);

  List<int> b;
  b.insert(0, 100);

  b = a;

  REQUIRE(b.getLength() == 3);
  REQUIRE(b.getEntry(0) == 1);
  REQUIRE(b.getEntry(1) == 2);
  REQUIRE(b.getEntry(2) == 3);

  a.setEntry(0, 50);

  // ensure deep copy
  REQUIRE(a.getEntry(0) == 50);
  REQUIRE(b.getEntry(0) == 1);
}

TEST_CASE("Priority: Testing List self assignment", "[list]") {
  List<int> lst;
  lst.insert(0, 7);
  lst.insert(1, 8);
  lst.insert(2, 9);

  lst = lst;

  REQUIRE(lst.getLength() == 3);
  REQUIRE(lst.getEntry(0) == 7);
  REQUIRE(lst.getEntry(1) == 8);
  REQUIRE(lst.getEntry(2) == 9);
}

TEST_CASE("Priority: Testing List iterator equality and traversal", "[iterator]") {
  List<int> lst;
  REQUIRE(lst.begin() == lst.end());

  lst.insert(0, 5);
  lst.insert(1, 6);
  lst.insert(2, 7);

  auto it = lst.begin();
  REQUIRE(it != lst.end());
  REQUIRE(*it == 5);

  ++it;
  REQUIRE(*it == 6);

  ++it;
  REQUIRE(*it == 7);

  ++it;
  REQUIRE(it == lst.end());
}

TEST_CASE("Priority: Testing Sorted List duplicates", "[sorted list]") {
  SortedList<int, List<int>> sort;

  sort.insert(5);
  sort.insert(2);
  sort.insert(5);
  sort.insert(3);
  sort.insert(2);

  REQUIRE(sort.getLength() == 5);
  REQUIRE(sort.getEntry(0) == 2);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getEntry(2) == 3);
  REQUIRE(sort.getEntry(3) == 5);
  REQUIRE(sort.getEntry(4) == 5);

  // should return first matching position
  REQUIRE(sort.getPosition(2) == 0);
  REQUIRE(sort.getPosition(3) == 2);
  REQUIRE(sort.getPosition(5) == 3);
}

TEST_CASE("Priority: Testing Sorted List remove by value with duplicates", "[sorted list]") {
  SortedList<int, List<int>> sort;

  sort.insert(4);
  sort.insert(1);
  sort.insert(4);
  sort.insert(2);

  // [1,2,4,4]
  sort.remove(4); // remove first 4 encountered
  REQUIRE(sort.getLength() == 3);
  REQUIRE(sort.getEntry(0) == 1);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getEntry(2) == 4);

  sort.remove(1);
  REQUIRE(sort.getLength() == 2);
  REQUIRE(sort.getEntry(0) == 2);
  REQUIRE(sort.getEntry(1) == 4);
}

TEST_CASE("Priority: Testing Sorted List clear", "[sorted list]") {
  SortedList<int, List<int>> sort;

  sort.insert(10);
  sort.insert(5);
  sort.insert(7);

  REQUIRE_FALSE(sort.isEmpty());
  REQUIRE(sort.getLength() == 3);

  sort.clear();

  REQUIRE(sort.isEmpty());
  REQUIRE(sort.getLength() == 0);
}

TEST_CASE("Priority: Testing Sorted List exceptions", "[sorted list]") {
  SortedList<int, List<int>> sort;

  REQUIRE_THROWS_AS(sort.remove(5), std::invalid_argument);
  REQUIRE_THROWS_AS(sort.getPosition(5), std::invalid_argument);
  REQUIRE_THROWS_AS(sort.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(sort.removeAt(0), std::out_of_range);

  sort.insert(1);
  sort.insert(3);
  sort.insert(5);

  REQUIRE_THROWS_AS(sort.getEntry(3), std::out_of_range);
  REQUIRE_THROWS_AS(sort.removeAt(3), std::out_of_range);
  REQUIRE_THROWS_AS(sort.remove(7), std::invalid_argument);
  REQUIRE_THROWS_AS(sort.getPosition(7), std::invalid_argument);
}

TEST_CASE("Priority: Testing Priority Queue peek and remove", "[priority queue]") {
  PriorityQueueType pq;

  pq.add(4);
  pq.add(1);
  pq.add(9);
  pq.add(3);

  REQUIRE_FALSE(pq.isEmpty());
  REQUIRE(pq.peek() == 9);

  pq.remove();
  REQUIRE(pq.peek() == 4);

  pq.remove();
  REQUIRE(pq.peek() == 3);

  pq.remove();
  REQUIRE(pq.peek() == 1);

  pq.remove();
  REQUIRE(pq.isEmpty());
}

TEST_CASE("Priority: Testing Priority Queue duplicate values", "[priority queue]") {
  PriorityQueueType pq;

  pq.add(5);
  pq.add(5);
  pq.add(2);
  pq.add(5);

  REQUIRE(pq.peek() == 5);
  pq.remove();
  REQUIRE(pq.peek() == 5);
  pq.remove();
  REQUIRE(pq.peek() == 5);
  pq.remove();
  REQUIRE(pq.peek() == 2);
  pq.remove();
  REQUIRE(pq.isEmpty());
}

TEST_CASE("Priority: Testing Priority Queue exceptions", "[priority queue]") {
  PriorityQueueType pq;

  REQUIRE_THROWS_AS(pq.peek(), std::out_of_range);
  REQUIRE_THROWS_AS(pq.remove(), std::out_of_range);

  pq.add(10);
  REQUIRE_NOTHROW(pq.peek());
  REQUIRE_NOTHROW(pq.remove());

  REQUIRE_THROWS_AS(pq.peek(), std::out_of_range);
  REQUIRE_THROWS_AS(pq.remove(), std::out_of_range);
}
