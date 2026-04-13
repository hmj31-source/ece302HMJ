#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "FrontierQueue.hpp"

/* Provided test cases */
TEST_CASE("Simple push test", "[FrontierQueue]")
{
    FrontierQueue<int> fq;
    REQUIRE(fq.empty());

    fq.push(1, 0, 1);

    REQUIRE_FALSE(fq.empty());
    REQUIRE(fq.contains(1));
}

TEST_CASE("Simple contains test", "[FrontierQueue]")
{
    FrontierQueue<int> fq;

    REQUIRE_FALSE(fq.contains(1));
    REQUIRE_FALSE(fq.contains(2));

    fq.push(1, 1, 1);
    fq.push(2, 2, 2);

    REQUIRE(fq.contains(1));
    REQUIRE(fq.contains(2));
    REQUIRE_FALSE(fq.contains(3));
}

TEST_CASE("Simple pop test", "[FrontierQueue]")
{
    FrontierQueue<int> fq;
    
    fq.push(1, 1, 1);

    State<int> state = fq.pop();
    REQUIRE(state.getValue() == 1);
    REQUIRE(state.getPathCost() == 1);
    REQUIRE(state.getFCost() == 2);
    REQUIRE(fq.empty());
}

TEST_CASE("Simple replaceif test", "[FrontierQueue]")
{
    FrontierQueue<int> fq;

    fq.push(1, 100, 100);

    fq.replaceif(1, 1);
    State<int> state = fq.pop();
    REQUIRE(state.getValue() == 1);
    REQUIRE(state.getPathCost() == 1);
    REQUIRE(state.getFCost() == 101);
}


/* Your test cases here */
TEST_CASE("Heap ordering after pop is correct", "[FrontierQueue]") {
    FrontierQueue<int> fq;

    fq.push(1, 5, 5);  // f = 10
    fq.push(2, 1, 1);  // f = 2
    fq.push(3, 2, 2);  // f = 4

    REQUIRE(fq.pop().getValue() == 2); // smallest f
    REQUIRE(fq.pop().getValue() == 3); // next smallest
    REQUIRE(fq.pop().getValue() == 1); // largest
}