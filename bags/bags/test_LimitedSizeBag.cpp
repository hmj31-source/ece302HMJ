#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "LimitedSizeBag.hpp"


TEST_CASE("Calling all public members", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

TEST_CASE("defalut constructor", "[LimitedSizeBag]"){
  LimitedSizeBag<int> bag;

  REQUIRE(bag.getCurrentSize() == 0);

}
TEST_CASE("Add increases size and contains works", "[LimitedSizeBag]") {
  LimitedSizeBag<int> bag;

  REQUIRE(bag.add(10) == true);
  REQUIRE(bag.getCurrentSize() == 1);
  REQUIRE(bag.isEmpty() == false);
  REQUIRE(bag.contains(10) == true);
  REQUIRE(bag.getFrequencyOf(10) == 1);

  REQUIRE(bag.add(20) == true);
  REQUIRE(bag.getCurrentSize() == 2);
  REQUIRE(bag.contains(20) == true);
  REQUIRE(bag.getFrequencyOf(20) == 1);
}

TEST_CASE("Remove removes one occurrence and updates size/frequency", "[LimitedSizeBag]") {
  LimitedSizeBag<int> bag;

  bag.add(5);
  bag.add(5);
  bag.add(7);

  REQUIRE(bag.getCurrentSize() == 3);
  REQUIRE(bag.getFrequencyOf(5) == 2);

  REQUIRE(bag.remove(5) == true);
  REQUIRE(bag.getCurrentSize() == 2);
  REQUIRE(bag.getFrequencyOf(5) == 1);

  REQUIRE(bag.remove(5) == true);
  REQUIRE(bag.getCurrentSize() == 1);
  REQUIRE(bag.getFrequencyOf(5) == 0);
  REQUIRE(bag.contains(5) == false);

  REQUIRE(bag.remove(5) == false); // nothing left to remove
  REQUIRE(bag.getCurrentSize() == 1);
}

TEST_CASE("Remove of non-existent item returns false and does not change size", "[LimitedSizeBag]") {
  LimitedSizeBag<int> bag;

  bag.add(1);
  bag.add(2);

  REQUIRE(bag.remove(99) == false);
  REQUIRE(bag.getCurrentSize() == 2);
  REQUIRE(bag.contains(1) == true);
  REQUIRE(bag.contains(2) == true);
}

TEST_CASE("Clear empties the bag", "[LimitedSizeBag]") {
  LimitedSizeBag<int> bag;

  bag.add(1);
  bag.add(2);
  bag.add(2);

  REQUIRE(bag.getCurrentSize() == 3);
  bag.clear();

  REQUIRE(bag.getCurrentSize() == 0);
  REQUIRE(bag.isEmpty() == true);
  REQUIRE(bag.contains(1) == false);
  REQUIRE(bag.getFrequencyOf(2) == 0);

  // After clear, you should be able to add again
  REQUIRE(bag.add(42) == true);
  REQUIRE(bag.getCurrentSize() == 1);
  REQUIRE(bag.contains(42) == true);
}

TEST_CASE("Bag respects max capacity of 100", "[LimitedSizeBag]") {
  LimitedSizeBag<int> bag;

  // Fill to capacity
  for (std::size_t i = 0; i < LimitedSizeBag<int>::maxsize; i++) {
    REQUIRE(bag.add(static_cast<int>(i)) == true);
  }

  REQUIRE(bag.getCurrentSize() == LimitedSizeBag<int>::maxsize);

  // One more should fail
  REQUIRE(bag.add(999) == false);
  REQUIRE(bag.getCurrentSize() == LimitedSizeBag<int>::maxsize);
}

TEST_CASE("Works with non-numeric types too (template sanity check)", "[LimitedSizeBag]") {
  LimitedSizeBag<std::string> bag;

  REQUIRE(bag.add("hi") == true);
  REQUIRE(bag.add("hi") == true);
  REQUIRE(bag.add("bye") == true);

  REQUIRE(bag.getFrequencyOf("hi") == 2);
  REQUIRE(bag.contains("bye") == true);

  REQUIRE(bag.remove("hi") == true);
  REQUIRE(bag.getFrequencyOf("hi") == 1);
}