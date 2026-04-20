#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "Graph.hpp"

/* Provided test case */
TEST_CASE("Test Construction", "[construction]") {
    Graph<int> g;
    REQUIRE(g.getNumVertices() == 0);
    REQUIRE(g.getNumEdges() == 0);
}

TEST_CASE("Graph: Test Add", "[graph]") {
    Graph<int> testGraph;

    REQUIRE(testGraph.getNumVertices() == 0);
    REQUIRE(testGraph.getNumEdges() == 0);

    REQUIRE(testGraph.add(5, 2));
    REQUIRE(testGraph.getNumVertices() == 2);
    REQUIRE(testGraph.getNumEdges() == 1);
}

TEST_CASE("Graph: Test Add 2", "[graph]") {
    Graph<int> testGraph;

    REQUIRE(testGraph.add(5, 2));
    REQUIRE(testGraph.add(10, 5));
    REQUIRE(testGraph.getNumVertices() == 3);
    REQUIRE(testGraph.getNumEdges() == 2);

    REQUIRE(testGraph.add(2, 10));
    REQUIRE(testGraph.getNumVertices() == 3);
    REQUIRE(testGraph.getNumEdges() == 3);
}

TEST_CASE("Graph: Test Add Duplicate", "[graph]") {
    Graph<int> testGraph;

    REQUIRE(testGraph.add(5, 2));
    REQUIRE_FALSE(testGraph.add(5, 2));
    REQUIRE(testGraph.getNumVertices() == 2);
    REQUIRE(testGraph.getNumEdges() == 1);
}

TEST_CASE("Graph: Test Undirected", "[graph]") {
    Graph<int> testGraph;

    REQUIRE(testGraph.add(5, 2));
    REQUIRE_FALSE(testGraph.add(2, 5));
    REQUIRE(testGraph.getNumVertices() == 2);
    REQUIRE(testGraph.getNumEdges() == 1);
}

TEST_CASE("Graph: Test Remove", "[graph]") {
    Graph<int> testGraph;

    REQUIRE(testGraph.add(5, 2));
    REQUIRE(testGraph.getNumVertices() == 2);
    REQUIRE(testGraph.getNumEdges() == 1);

    REQUIRE(testGraph.remove(5, 2));
    REQUIRE(testGraph.getNumVertices() == 0);
    REQUIRE(testGraph.getNumEdges() == 0);
}

TEST_CASE("Graph: Test Remove 2", "[graph]") {
    Graph<int> testGraph;

    REQUIRE(testGraph.add(5, 2));
    REQUIRE(testGraph.add(10, 5));
    REQUIRE(testGraph.getNumVertices() == 3);
    REQUIRE(testGraph.getNumEdges() == 2);

    REQUIRE(testGraph.add(10, 2));
    REQUIRE(testGraph.getNumVertices() == 3);
    REQUIRE(testGraph.getNumEdges() == 3);

    REQUIRE(testGraph.remove(10, 2));
    REQUIRE(testGraph.getNumVertices() == 3);
    REQUIRE(testGraph.getNumEdges() == 2);

    REQUIRE(testGraph.remove(10, 5));
    REQUIRE(testGraph.getNumVertices() == 2);
    REQUIRE(testGraph.getNumEdges() == 1);
}

TEST_CASE("Graph: Test Remove False", "[graph]") {
    Graph<int> testGraph;

    REQUIRE_FALSE(testGraph.remove(5, 2));

    REQUIRE(testGraph.add(5, 2));
    REQUIRE_FALSE(testGraph.remove(10, 5));

    REQUIRE(testGraph.add(10, 5));
    REQUIRE(testGraph.add(10, 2));
    REQUIRE(testGraph.remove(5, 2));
    REQUIRE_FALSE(testGraph.remove(5, 2));
}

TEST_CASE("Graph: Test Remove then Add", "[graph]") {
    Graph<int> testGraph;

    REQUIRE(testGraph.add(5, 2));
    REQUIRE(testGraph.getNumVertices() == 2);
    REQUIRE(testGraph.getNumEdges() == 1);

    REQUIRE(testGraph.remove(5, 2));
    REQUIRE(testGraph.getNumVertices() == 0);
    REQUIRE(testGraph.getNumEdges() == 0);

    REQUIRE(testGraph.add(5, 2));
    REQUIRE(testGraph.getNumVertices() == 2);
    REQUIRE(testGraph.getNumEdges() == 1);
}

TEST_CASE("Graph: Test Add Disconnected", "[graph]") {
    Graph<int> testGraph;

    REQUIRE(testGraph.add(5, 2));
    REQUIRE_FALSE(testGraph.add(10, 3));
    REQUIRE(testGraph.getNumVertices() == 2);
    REQUIRE(testGraph.getNumEdges() == 1);
}

TEST_CASE("Graph: Test Self Edge False", "[graph]") {
    Graph<int> testGraph;

    REQUIRE_FALSE(testGraph.add(7, 7));
    REQUIRE(testGraph.getNumVertices() == 0);
    REQUIRE(testGraph.getNumEdges() == 0);
}