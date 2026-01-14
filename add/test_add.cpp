#define CATCH_CONFIG_MAIN
#include <iostream>
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
  //break here
  REQUIRE(a.call(1.5,2.5)==4);
}

TEST_CASE("Test bool add", "[Add]"){

  Add<bool> a;
  REQUIRE(a.call(false, false)== false);
  std::cout << "passed 1st case" << std::endl;
  REQUIRE(a.call(false, true)== true);
  std::cout << "passed 2nd case" << std::endl;
  REQUIRE(a.call(true, true)== true);
  std::cout << "passed 3rd case" << std::endl;
}