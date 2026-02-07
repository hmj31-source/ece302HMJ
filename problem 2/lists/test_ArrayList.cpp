#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ArrayList.hpp"

TEST_CASE("ArrayList: isEmpty + getLength", "[ArrayList]") {
    ArrayList<int> list;

    REQUIRE(list.isEmpty());
    REQUIRE(list.getLength() == 0);
}

TEST_CASE("ArrayList: insert + getEntry", "[ArrayList]") {
    ArrayList<int> list;

    list.insert(0, 10);
    list.insert(1, 20);
    list.insert(2, 30);

    REQUIRE(list.getLength() == 3);
    REQUIRE(list.getEntry(0) == 10);
    REQUIRE(list.getEntry(1) == 20);
    REQUIRE(list.getEntry(2) == 30);
}

TEST_CASE("ArrayList: insert in middle", "[ArrayList]") {
    ArrayList<int> list;

    list.insert(0, 10);
    list.insert(1, 30);
    list.insert(1, 20);  // middle insert

    REQUIRE(list.getEntry(0) == 10);
    REQUIRE(list.getEntry(1) == 20);
    REQUIRE(list.getEntry(2) == 30);
}

TEST_CASE("ArrayList: remove", "[ArrayList]") {
    ArrayList<int> list;

    list.insert(0, 10);
    list.insert(1, 20);
    list.insert(2, 30);

    list.remove(1);

    REQUIRE(list.getLength() == 2);
    REQUIRE(list.getEntry(0) == 10);
    REQUIRE(list.getEntry(1) == 30);
}

TEST_CASE("ArrayList: setEntry", "[ArrayList]") {
    ArrayList<int> list;

    list.insert(0, 5);
    list.setEntry(0, 99);

    REQUIRE(list.getEntry(0) == 99);
}

TEST_CASE("ArrayList: clear", "[ArrayList]") {
    ArrayList<int> list;

    list.insert(0, 1);
    list.insert(1, 2);

    list.clear();

    REQUIRE(list.isEmpty());
    REQUIRE(list.getLength() == 0);
}

TEST_CASE("ArrayList: invalid bounds", "[ArrayList]") {
    ArrayList<int> list;

    REQUIRE_THROWS_AS(list.insert(1, 5), std::out_of_range);
    REQUIRE_THROWS_AS(list.remove(0), std::out_of_range);
}
