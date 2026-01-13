#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Add.hpp"

/* Provided tests */

TEST_CASE("Test add", "[Add]"){

  Add<int> a;
  REQUIRE(a.call(1,2)==3);
}

/* Your tests here */

TEST_CASE("Test string add", "[Add]"){

  Add<std::string> a;
  REQUIRE(a.call("one","two")== "onetwo");
}

TEST_CASE("Test double add", "[Add]"){

  Add<double> a;
  REQUIRE(a.call(1.5,2.5)==4);
}

TEST_CASE("Test bool add", "[Add]"){

  Add<bool> a;
  REQUIRE(a.call(false, false)== false);
  REQUIRE(a.call(false, true)== true);
  REQUIRE(a.call(true, true)== true);

}