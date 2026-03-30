#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "List.hpp"
#include "Queue.hpp"

/* Provided test cases */
TEST_CASE("Queue: Testing Enqueue", "[queue]") {

  Queue<int, List<int>> queue;

  REQUIRE(queue.isEmpty());
  queue.enqueue(12);
  REQUIRE_FALSE(queue.isEmpty());

}

/* Your test cases here */
TEST_CASE("Queue: FIFO behavior", "[queue]") {
  Queue<int, List<int>> queue;

  queue.enqueue(10);
  queue.enqueue(20);
  queue.enqueue(30);

  REQUIRE(queue.peekFront() == 10);

  queue.dequeue();
  REQUIRE(queue.peekFront() == 20);

  queue.dequeue();
  REQUIRE(queue.peekFront() == 30);

  queue.dequeue();
  REQUIRE(queue.isEmpty());
}

TEST_CASE("Queue: Single element dequeue", "[queue]") {
  Queue<int, List<int>> queue;

  queue.enqueue(99);
  REQUIRE_FALSE(queue.isEmpty());
  REQUIRE(queue.peekFront() == 99);

  queue.dequeue();
  REQUIRE(queue.isEmpty());
}

TEST_CASE("Queue: Multiple enqueue and dequeue", "[queue]") {
  Queue<int, List<int>> queue;

  for(int i = 0; i < 5; ++i) {
    queue.enqueue(i);
  }

  for(int i = 0; i < 5; ++i) {
    REQUIRE(queue.peekFront() == i);
    queue.dequeue();
  }

  REQUIRE(queue.isEmpty());
}

TEST_CASE("Queue: Empty queue operations throw", "[queue]") {
  Queue<int, List<int>> queue;

  REQUIRE_THROWS_AS(queue.peekFront(), std::out_of_range);
  REQUIRE_THROWS_AS(queue.dequeue(), std::out_of_range);
}