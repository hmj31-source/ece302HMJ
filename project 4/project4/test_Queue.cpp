#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <stdexcept>
#include <string>

#include "List.hpp"
#include "Queue.hpp"

/* Provided test case */
TEST_CASE("Queue: Testing Enqueue", "[queue]") {
  Queue<int, List<int>> queue;

  REQUIRE(queue.isEmpty());
  queue.enqueue(12);
  REQUIRE_FALSE(queue.isEmpty());
}

/* Additional test cases */

TEST_CASE("Queue: PeekFront after enqueue", "[queue]") {
  Queue<int, List<int>> queue;

  queue.enqueue(12);
  REQUIRE(queue.peekFront() == 12);
  REQUIRE_FALSE(queue.isEmpty());
}

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

TEST_CASE("Queue: PeekFront does not remove item", "[queue]") {
  Queue<int, List<int>> queue;

  queue.enqueue(5);
  queue.enqueue(6);

  REQUIRE(queue.peekFront() == 5);
  REQUIRE(queue.peekFront() == 5);
  REQUIRE_FALSE(queue.isEmpty());

  queue.dequeue();
  REQUIRE(queue.peekFront() == 6);
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

TEST_CASE("Queue: Interleaved operations preserve FIFO", "[queue]") {
  Queue<int, List<int>> queue;

  queue.enqueue(1);
  queue.enqueue(2);
  queue.dequeue();              // removes 1
  queue.enqueue(3);

  REQUIRE(queue.peekFront() == 2);
  queue.dequeue();
  REQUIRE(queue.peekFront() == 3);
  queue.dequeue();

  REQUIRE(queue.isEmpty());
}

TEST_CASE("Queue: Queue can be reused after becoming empty", "[queue]") {
  Queue<int, List<int>> queue;

  queue.enqueue(7);
  queue.dequeue();
  REQUIRE(queue.isEmpty());

  queue.enqueue(8);
  REQUIRE_FALSE(queue.isEmpty());
  REQUIRE(queue.peekFront() == 8);

  queue.dequeue();
  REQUIRE(queue.isEmpty());
}

TEST_CASE("Queue: Longer mixed sequence", "[queue]") {
  Queue<int, List<int>> queue;

  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  REQUIRE(queue.peekFront() == 1);

  queue.dequeue(); // removes 1
  REQUIRE(queue.peekFront() == 2);

  queue.enqueue(4);
  queue.enqueue(5);

  REQUIRE(queue.peekFront() == 2);
  queue.dequeue(); // removes 2
  REQUIRE(queue.peekFront() == 3);

  queue.dequeue(); // removes 3
  REQUIRE(queue.peekFront() == 4);

  queue.dequeue(); // removes 4
  REQUIRE(queue.peekFront() == 5);

  queue.dequeue(); // removes 5
  REQUIRE(queue.isEmpty());
}

TEST_CASE("Queue: Works with std::string", "[queue]") {
  Queue<std::string, List<std::string>> queue;

  queue.enqueue("first");
  queue.enqueue("second");

  REQUIRE(queue.peekFront() == "first");
  queue.dequeue();
  REQUIRE(queue.peekFront() == "second");
  queue.dequeue();

  REQUIRE(queue.isEmpty());
}

TEST_CASE("Queue: Empty queue operations throw", "[queue]") {
  Queue<int, List<int>> queue;

  REQUIRE_THROWS_AS(queue.peekFront(), std::out_of_range);
  REQUIRE_THROWS_AS(queue.dequeue(), std::out_of_range);
}

TEST_CASE("Queue: Dequeue until empty then throw", "[queue]") {
  Queue<int, List<int>> queue;

  queue.enqueue(11);
  queue.enqueue(22);

  queue.dequeue();
  queue.dequeue();

  REQUIRE(queue.isEmpty());
  REQUIRE_THROWS_AS(queue.peekFront(), std::out_of_range);
  REQUIRE_THROWS_AS(queue.dequeue(), std::out_of_range);
}