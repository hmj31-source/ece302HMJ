#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "Database.hpp"


// struct used just for testing
struct TestEntry {
    std::string title;
    std::string author;
    int pubYear;
};
// TestEntry operators
bool operator==(const TestEntry& e1, const TestEntry& e2) {
    return (e1.title == e2.title) && (e1.author == e2.author) && (e1.pubYear == e2.pubYear);
};
std::ostream& operator<<(std::ostream& os, const TestEntry& t)
{
    os << "Title: " << t.title << ", Author: " << t.author << ", Year: " << t.pubYear;
    return os;
}


/* Provided test cases */
TEST_CASE("Test Add and Contains", "[add]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    REQUIRE(testdb.isEmpty());
    REQUIRE(testdb.add("key1", "key2", e1));
    REQUIRE_FALSE(testdb.isEmpty());
    REQUIRE(testdb.contains("key1"));
    REQUIRE(testdb.contains("key2"));
}


TEST_CASE("Test getValue", "[retrieve]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);
    
    REQUIRE(testdb.getValue("key1") == e1);
    REQUIRE(testdb.getValue("key2") == e1);
}


TEST_CASE("Test Remove", "[remove]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);
    
    testdb.remove("key1");
    REQUIRE(!testdb.contains("key1"));
    REQUIRE(!testdb.contains("key2"));

    testdb.add("key1", "key2", e1);
    
    testdb.remove("key2");
    REQUIRE(!testdb.contains("key1"));
    REQUIRE(!testdb.contains("key2"));

    REQUIRE(testdb.isEmpty());
}


TEST_CASE("Test Copy", "[copy]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);

    Database<std::string> testdb_copy(testdb);

    testdb.clear();

    REQUIRE(testdb_copy.getValue("key1") == e1);
    REQUIRE(testdb_copy.getValue("key2") == e1); 
    
    Database<std::string> testdb2;

    testdb2.add("key1", "key2", e1);

    Database<std::string> testdb2_copy;

    testdb2_copy = testdb2;

    testdb2.clear();

    REQUIRE(testdb2_copy.getValue("key1") == e1);
    REQUIRE(testdb2_copy.getValue("key2") == e1); 
}


TEST_CASE("TestEntry Type", "[entry type]") {
    Database<TestEntry> testdb;

    TestEntry e1;
    std::string isbn1 = "000-0-00-000000-1";
    std::string catalog_id1 = "0000001";
    e1.title = "The Winds of Winter";
    e1.author = "George R. R. Martin";
    e1.pubYear = 2051;

    testdb.add(isbn1, catalog_id1, e1);

    TestEntry e2;

    std::string isbn2 = "000-0-00-000000-2";
    std::string catalog_id2 = "0000002";
    e2.title = "A Dream of Spring";
    e2.author = "George R. R. Martin";
    e2.pubYear = 2052;

    testdb.add(isbn2, catalog_id2, e2);

    // TODO
    
}


/* Your test cases here */
TEST_CASE("Duplicate keys are rejected", "[add][duplicate]") {
    Database<std::string> db;
    REQUIRE(db.add("a", "b", "first"));
    REQUIRE_FALSE(db.add("a", "c", "second"));
    REQUIRE_FALSE(db.add("d", "b", "third"));
    REQUIRE(db.getNumberOfEntries() == 1);
}

TEST_CASE("Remove by second key removes both lookups", "[remove]") {
    Database<std::string> db;
    db.add("isbn1", "id1", "book1");

    REQUIRE(db.contains("isbn1"));
    REQUIRE(db.contains("id1"));

    REQUIRE(db.remove("id1"));
    REQUIRE_FALSE(db.contains("isbn1"));
    REQUIRE_FALSE(db.contains("id1"));
    REQUIRE(db.isEmpty());
}

TEST_CASE("Middle removal keeps moved item retrievable", "[remove][reindex]") {
    Database<std::string> db;

    db.add("k1", "a1", "one");
    db.add("k2", "a2", "two");
    db.add("k3", "a3", "three");

    REQUIRE(db.remove("k2"));

    REQUIRE_FALSE(db.contains("k2"));
    REQUIRE_FALSE(db.contains("a2"));

    REQUIRE(db.contains("k1"));
    REQUIRE(db.contains("a1"));
    REQUIRE(db.getValue("k1") == "one");

    REQUIRE(db.contains("k3"));
    REQUIRE(db.contains("a3"));
    REQUIRE(db.getValue("k3") == "three");
}

TEST_CASE("Clear empties database", "[clear]") {
    Database<std::string> db;
    db.add("x", "y", "val");
    db.clear();

    REQUIRE(db.isEmpty());
    REQUIRE(db.getNumberOfEntries() == 0);
    REQUIRE_FALSE(db.contains("x"));
    REQUIRE_FALSE(db.contains("y"));
}

TEST_CASE("TestEntry retrieval by both keys", "[entry type]") {
    Database<TestEntry> testdb;

    TestEntry e1{"The Winds of Winter", "George R. R. Martin", 2051};
    TestEntry e2{"A Dream of Spring", "George R. R. Martin", 2052};

    std::string isbn1 = "000-0-00-000000-1";
    std::string catalog_id1 = "0000001";
    std::string isbn2 = "000-0-00-000000-2";
    std::string catalog_id2 = "0000002";

    REQUIRE(testdb.add(isbn1, catalog_id1, e1));
    REQUIRE(testdb.add(isbn2, catalog_id2, e2));

    REQUIRE(testdb.getValue(isbn1) == e1);
    REQUIRE(testdb.getValue(catalog_id1) == e1);
    REQUIRE(testdb.getValue(isbn2) == e2);
    REQUIRE(testdb.getValue(catalog_id2) == e2);
}