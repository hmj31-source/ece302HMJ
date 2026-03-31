#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "BinarySearchTree.hpp"

/* Provided test cases */

TEST_CASE("BST: Test Insert", "[insert]") {
    BinarySearchTree<int, int> bst1;

    REQUIRE(bst1.isEmpty());

    bst1.insert(10, 10);
    REQUIRE_FALSE(bst1.isEmpty());
}

TEST_CASE("BST: Test Duplicate Insert", "[duplicate insert]") {
    BinarySearchTree<int, int> bst1;
    
    REQUIRE(bst1.insert(12, 12));
    REQUIRE(!bst1.insert(12, 12));
}

TEST_CASE("BST: Test Remove With No Children", "[remove]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);

    int item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));

    bst1.remove(5);
    REQUIRE_FALSE(bst1.retrieve(5, item));

    bst1.remove(15);
    REQUIRE_FALSE(bst1.retrieve(15, item));

    bst1.remove(10);
    REQUIRE_FALSE(bst1.retrieve(10, item));

    REQUIRE(bst1.isEmpty());
}

TEST_CASE("BST: Test Copy Assign", "[copy assign]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(50, 50);
    bst1.insert(0, 0);
    bst1.insert(100, 100);
    bst1.insert(25, 25);
    bst1.insert(75, 75);

    BinarySearchTree<int, int> bst2;

    bst2 = bst1;

    bst1.destroy();

    REQUIRE(bst1.isEmpty());

    REQUIRE_FALSE(bst2.isEmpty());

    int item;
    REQUIRE(bst2.retrieve(100, item));
    REQUIRE(bst2.retrieve(75, item));
    REQUIRE(bst2.retrieve(50, item));
    REQUIRE(bst2.retrieve(25, item));
    REQUIRE_FALSE(bst2.retrieve(51, item));
}

/* Your test cases here */
TEST_CASE("BST: Test Retrieve", "[retrieve]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);
    bst1.insert(12, 12);
    bst1.insert(18, 18);

    int item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(item == 10);

    REQUIRE(bst1.retrieve(12, item));
    REQUIRE(item == 12);

    REQUIRE(bst1.retrieve(18, item));
    REQUIRE(item == 18);

    REQUIRE_FALSE(bst1.retrieve(99, item));
}

TEST_CASE("BST: Test Remove With 1 Left Child", "[remove]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(2, 2);

    int item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(2, item));

    bst1.remove(5);

    REQUIRE_FALSE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(2, item));
    REQUIRE(bst1.retrieve(10, item));
}

TEST_CASE("BST: Test Remove With 1 Right Child", "[remove]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(10, 10);
    bst1.insert(15, 15);
    bst1.insert(12, 12);

    int item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(12, item));

    bst1.remove(15);

    REQUIRE_FALSE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(12, item));
    REQUIRE(bst1.retrieve(10, item));
}

TEST_CASE("BST: Test Remove With 2 children", "[remove]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);
    bst1.insert(12, 12);
    bst1.insert(18, 18);

    int item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(12, item));
    REQUIRE(bst1.retrieve(18, item));

    bst1.remove(15);

    REQUIRE_FALSE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(12, item));
    REQUIRE(bst1.retrieve(18, item));
    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
}

TEST_CASE("BST: Test Remove Root With 1 Left Child", "[remove]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);

    int item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));

    bst1.remove(10);

    REQUIRE_FALSE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
}

TEST_CASE("BST: Test Remove Root With 1 Right Child", "[remove]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(10, 10);
    bst1.insert(15, 15);

    int item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(15, item));

    bst1.remove(10);

    REQUIRE_FALSE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(15, item));
}

TEST_CASE("BST: Test Remove Nonexistent Key", "[remove]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);

    int item;

    REQUIRE_FALSE(bst1.remove(100));
    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));
}

TEST_CASE("BST: Test Copy Constructor", "[copy constructor]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(20, 20);
    bst1.insert(10, 10);
    bst1.insert(30, 30);
    bst1.insert(25, 25);

    BinarySearchTree<int, int> bst2(bst1);

    bst1.destroy();

    REQUIRE(bst1.isEmpty());

    int item;
    REQUIRE(bst2.retrieve(20, item));
    REQUIRE(bst2.retrieve(10, item));
    REQUIRE(bst2.retrieve(30, item));
    REQUIRE(bst2.retrieve(25, item));
    REQUIRE_FALSE(bst2.retrieve(99, item));
}

TEST_CASE("BST: Test Char Item Type", "[char type]") {
    BinarySearchTree<int, char> bst1;

    bst1.insert(10, 'a');
    bst1.insert(5, 'b');
    bst1.insert(15, 'c');

    char item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(item == 'a');

    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(item == 'b');

    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(item == 'c');

    bst1.remove(10);

    REQUIRE_FALSE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));
}