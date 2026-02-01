#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "DynamicBag.hpp"


TEST_CASE("Calling all public members", "[DynamicBag]"){
  DynamicBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

TEST_CASE("Default constructor starts empty", "[DynamicBag]") {
  DynamicBag<int> bag;

  REQUIRE(bag.getCurrentSize() == 0);
  REQUIRE(bag.isEmpty() == true);
  REQUIRE(bag.contains(1) == false);
  REQUIRE(bag.getFrequencyOf(1) == 0);
}

TEST_CASE("Add works and dynamically grows", "[DynamicBag]") {
  DynamicBag<int> bag;

  REQUIRE(bag.add(10) == true);
  REQUIRE(bag.add(20) == true);
  REQUIRE(bag.add(30) == true);

  REQUIRE(bag.getCurrentSize() == 3);
  REQUIRE(bag.contains(10) == true);
  REQUIRE(bag.contains(20) == true);
  REQUIRE(bag.contains(30) == true);
}

TEST_CASE("Remove removes one occurrence only", "[DynamicBag]") {
  DynamicBag<int> bag;

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
  REQUIRE(bag.contains(5) == false);

  REQUIRE(bag.remove(5) == false); // nothing left
}

TEST_CASE("Remove non-existent item does nothing", "[DynamicBag]") {
  DynamicBag<int> bag;

  bag.add(1);
  bag.add(2);

  REQUIRE(bag.remove(99) == false);
  REQUIRE(bag.getCurrentSize() == 2);
}

TEST_CASE("Clear empties the bag but keeps it usable", "[DynamicBag]") {
  DynamicBag<int> bag;

  bag.add(1);
  bag.add(2);
  bag.add(3);

  REQUIRE(bag.getCurrentSize() == 3);

  bag.clear();

  REQUIRE(bag.getCurrentSize() == 0);
  REQUIRE(bag.isEmpty() == true);

  // Can still add after clear
  REQUIRE(bag.add(42) == true);
  REQUIRE(bag.getCurrentSize() == 1);
  REQUIRE(bag.contains(42) == true);
}

TEST_CASE("Copy constructor makes deep copy", "[DynamicBag]") {
  DynamicBag<int> a;
  a.add(1);
  a.add(2);

  DynamicBag<int> b(a); // copy ctor

  REQUIRE(b.getCurrentSize() == 2);
  REQUIRE(b.contains(1) == true);
  REQUIRE(b.contains(2) == true);

  // Modify original
  a.remove(1);

  REQUIRE(a.getCurrentSize() == 1);
  REQUIRE(b.getCurrentSize() == 2); // unchanged
}

TEST_CASE("Copy assignment uses copy-swap correctly", "[DynamicBag]") {
  DynamicBag<int> a;
  a.add(1);
  a.add(2);

  DynamicBag<int> b;
  b.add(99);

  b = a;  // assignment

  REQUIRE(b.getCurrentSize() == 2);
  REQUIRE(b.contains(1) == true);
  REQUIRE(b.contains(2) == true);
}

TEST_CASE("Template works with non-numeric types", "[DynamicBag]") {
  DynamicBag<std::string> bag;

  bag.add("hi");
  bag.add("hi");
  bag.add("bye");

  REQUIRE(bag.getFrequencyOf("hi") == 2);
  REQUIRE(bag.contains("bye") == true);

  REQUIRE(bag.remove("hi") == true);
  REQUIRE(bag.getFrequencyOf("hi") == 1);
}