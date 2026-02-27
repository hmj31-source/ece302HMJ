#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "List.hpp"
#include "sort.hpp"

/* Provided test cases */
TEST_CASE("Sort: Test move entry", "[sorting]") {
  List<int> lst;

  lst.insert(0, 100);
  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 25);
  lst.insert(4, 11);

  // move forward
  lst.moveEntry(0, 2);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(0) == 4);
  REQUIRE(lst.getEntry(1) == 10);
  REQUIRE(lst.getEntry(2) == 100);
  REQUIRE(lst.getEntry(3) == 25);
  REQUIRE(lst.getEntry(4) == 11);

  // move backward
  lst.moveEntry(4, 0);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(0) == 11);
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 100);
  REQUIRE(lst.getEntry(4) == 25);

  // invalid moves
  REQUIRE_THROWS_AS(lst.moveEntry(5,0), std::out_of_range);
  REQUIRE_THROWS_AS(lst.moveEntry(0,5), std::out_of_range);
}


TEST_CASE("Sort: Integer sorting", "[sorting]"){

  List<int> lst;

  lst.insert(0, 100);
  lst.insert(1, 25);
  lst.insert(2, 10);
  lst.insert(3, 4);
  lst.insert(4, 11);

  quick_sort(lst, 0, lst.getLength()-1);

  // check sorted list
  REQUIRE(lst.getEntry(0) == 4);
  REQUIRE(lst.getEntry(1) == 10);
  REQUIRE(lst.getEntry(2) == 11);
  REQUIRE(lst.getEntry(3) == 25);
  REQUIRE(lst.getEntry(4) == 100);
}

TEST_CASE("Sort: Test partitioning", "[sorting]") {
    List<int> lst;
  
    lst.insert(0, 100);
    lst.insert(1, 30);
    lst.insert(2, 50);
    lst.insert(3, 4);
    lst.insert(4, 256);
    lst.insert(5, 1);
    lst.insert(6, 0);
    lst.insert(7, 25);
    lst.insert(8, 10);
    lst.insert(9, 512);
  
    // partition whole list
    int test = partition(lst, 0, lst.getLength()-1);
    // first item (100) should now be at index 7
    REQUIRE(test == 7);
}

/* Your test cases here */
// ---------- Edge cases: empty + single ----------
TEST_CASE("Sort: Empty list", "[sorting]") {
  List<int> lst;
  REQUIRE(lst.getLength() == 0);

  // should not throw, should remain empty
  quick_sort(lst, 0, -1);
  REQUIRE(lst.getLength() == 0);
}

TEST_CASE("Sort: Single element list", "[sorting]") {
  List<int> lst;
  lst.insert(0, 42);

  quick_sort(lst, 0, lst.getLength() - 1);

  REQUIRE(lst.getLength() == 1);
  REQUIRE(lst.getEntry(0) == 42);
}

// ---------- Already sorted + reverse sorted ----------
TEST_CASE("Sort: Already sorted integers", "[sorting]") {
  List<int> lst;
  lst.insert(0, 1);
  lst.insert(1, 2);
  lst.insert(2, 3);
  lst.insert(3, 4);
  lst.insert(4, 5);

  quick_sort(lst, 0, lst.getLength() - 1);

  REQUIRE(lst.getEntry(0) == 1);
  REQUIRE(lst.getEntry(1) == 2);
  REQUIRE(lst.getEntry(2) == 3);
  REQUIRE(lst.getEntry(3) == 4);
  REQUIRE(lst.getEntry(4) == 5);
}

TEST_CASE("Sort: Reverse sorted integers", "[sorting]") {
  List<int> lst;
  lst.insert(0, 9);
  lst.insert(1, 7);
  lst.insert(2, 5);
  lst.insert(3, 3);
  lst.insert(4, 1);

  quick_sort(lst, 0, lst.getLength() - 1);

  REQUIRE(lst.getEntry(0) == 1);
  REQUIRE(lst.getEntry(1) == 3);
  REQUIRE(lst.getEntry(2) == 5);
  REQUIRE(lst.getEntry(3) == 7);
  REQUIRE(lst.getEntry(4) == 9);
}

// ---------- Larger list ----------
TEST_CASE("Sort: Larger integer list", "[sorting]") {
  List<int> lst;
  // Unique values
  int vals[] = {42, 7, 99, 13, 0, 88, 23, 5, 67, 1};
  for (int i = 0; i < 10; ++i) lst.insert(i, vals[i]);

  quick_sort(lst, 0, lst.getLength() - 1);

  // Verify ascending order via adjacent comparisons
  for (std::size_t i = 1; i < lst.getLength(); ++i) {
    REQUIRE(lst.getEntry(i - 1) < lst.getEntry(i));
  }

  // Spot-check extremes
  REQUIRE(lst.getEntry(0) == 0);
  REQUIRE(lst.getEntry(lst.getLength() - 1) == 99);
}

// ---------- Double sorting ----------
TEST_CASE("Sort: Double sorting", "[sorting]") {
  List<double> lst;
  lst.insert(0, 3.14);
  lst.insert(1, 2.71);
  lst.insert(2, 1.41);
  lst.insert(3, 0.577);
  lst.insert(4, 4.2);

  quick_sort(lst, 0, lst.getLength() - 1);

  // verify increasing (no duplicates assumed)
  for (std::size_t i = 1; i < lst.getLength(); ++i) {
    REQUIRE(lst.getEntry(i - 1) < lst.getEntry(i));
  }

  // check first is ~0.577 and last is ~4.2
  const double eps = 1e-12;
  REQUIRE(std::abs(lst.getEntry(0) - 0.577) <= eps);
  REQUIRE(std::abs(lst.getEntry(4) - 4.2) <= eps);
}

// ---------- Char sorting ----------
TEST_CASE("Sort: Character sorting", "[sorting]") {
  List<char> lst;
  lst.insert(0, 'd');
  lst.insert(1, 'a');
  lst.insert(2, 'c');
  lst.insert(3, 'b');
  lst.insert(4, 'e');

  quick_sort(lst, 0, lst.getLength() - 1);

  REQUIRE(lst.getEntry(0) == 'a');
  REQUIRE(lst.getEntry(1) == 'b');
  REQUIRE(lst.getEntry(2) == 'c');
  REQUIRE(lst.getEntry(3) == 'd');
  REQUIRE(lst.getEntry(4) == 'e');
}

// ---------- String sorting (lexicographic) ----------
TEST_CASE("Sort: String sorting", "[sorting]") {
  List<std::string> lst;
  lst.insert(0, "pear");
  lst.insert(1, "apple");
  lst.insert(2, "orange");
  lst.insert(3, "banana");
  lst.insert(4, "grape");

  quick_sort(lst, 0, lst.getLength() - 1);

  REQUIRE(lst.getEntry(0) == "apple");
  REQUIRE(lst.getEntry(1) == "banana");
  REQUIRE(lst.getEntry(2) == "grape");
  REQUIRE(lst.getEntry(3) == "orange");
  REQUIRE(lst.getEntry(4) == "pear");
}

// ---------- Sort a subrange only ----------
TEST_CASE("Sort: Subrange quick_sort does not disturb outside", "[sorting]") {
  List<int> lst;
  // [50, 3, 2, 1, 4, 60]
  lst.insert(0, 50);
  lst.insert(1, 3);
  lst.insert(2, 2);
  lst.insert(3, 1);
  lst.insert(4, 4);
  lst.insert(5, 60);

  // sort only indices 1..4
  quick_sort(lst, 1, 4);

  // outside should remain unchanged
  REQUIRE(lst.getEntry(0) == 50);
  REQUIRE(lst.getEntry(5) == 60);

  // inside should now be [1,2,3,4]
  REQUIRE(lst.getEntry(1) == 1);
  REQUIRE(lst.getEntry(2) == 2);
  REQUIRE(lst.getEntry(3) == 3);
  REQUIRE(lst.getEntry(4) == 4);
}

// ---------- Partition properties test ----------
TEST_CASE("Sort: Partition property check", "[sorting]") {
  List<int> lst;
  // pivot = first = 20
  int vals[] = {20, 5, 30, 1, 25, 10, 40};
  for (int i = 0; i < 7; ++i) lst.insert(i, vals[i]);

  int p = partition(lst, 0, lst.getLength() - 1);

  // pivot should be at index p, and equal to 20
  REQUIRE(lst.getEntry((std::size_t)p) == 20);

  // everything left of pivot < 20
  for (int i = 0; i < p; ++i)
    REQUIRE(lst.getEntry((std::size_t)i) < 20);

  // everything right of pivot > 20 (no duplicates assumption)
  for (std::size_t i = (std::size_t)p + 1; i < lst.getLength(); ++i)
    REQUIRE(lst.getEntry(i) > 20);
}
