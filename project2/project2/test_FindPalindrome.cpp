#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

/* Provided test cases */

TEST_CASE("Test recursion", "[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);
}
/* Your test cases here */

TEST_CASE("Reject invalid words (non-letters)", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE_FALSE(b.add(""));        // empty
    REQUIRE_FALSE(b.add("a1"));      // digit
    REQUIRE_FALSE(b.add("a-b"));     // punctuation
    REQUIRE_FALSE(b.add("a b"));     // space
    REQUIRE_FALSE(b.add("!"));       // punctuation only

    REQUIRE(b.number() == 0);
    REQUIRE(b.toVector().empty());
}

TEST_CASE("Uniqueness is case-insensitive", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE(b.add("Bat"));
    REQUIRE_FALSE(b.add("bat"));
    REQUIRE_FALSE(b.add("BAT"));

    // still only one word, but there are no palindrome sentences with 1 non-pal word
    // (depends on whether single word counts as palindrome; your recursion will treat it as a sentence)
    // We avoid assuming that here:
    REQUIRE(b.toVector().size() == static_cast<size_t>(b.number()));
}

TEST_CASE("cutTest1: if more than one odd letter count, there are 0 palindromes", "[FindPalindrome]") {
    FindPalindrome b;

    // "ab" has a:1 b:1 -> two odds -> impossible
    REQUIRE(b.add("ab"));
    REQUIRE(b.number() == 0);

    // Adding another word might make it possible, but with just "ab" it's not
    REQUIRE(b.toVector().empty());
}

TEST_CASE("Known palindrome pair: bat + tab gives 2 palindromes", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE(b.add("bat"));
    REQUIRE(b.add("tab"));

    // Two permutations, both palindromes: battab and tabbat
    REQUIRE(b.number() == 2);

    auto pals = b.toVector();
    REQUIRE(pals.size() == 2);

    // check each sentence uses exactly 2 words
    REQUIRE(pals[0].size() == 2);
    REQUIRE(pals[1].size() == 2);

    // check contents are the same multiset {"bat","tab"} for both
    auto s0 = pals[0][0] + pals[0][1];
    auto s1 = pals[1][0] + pals[1][1];
    REQUIRE((s0 == "battab" || s0 == "tabbat"));
    REQUIRE((s1 == "battab" || s1 == "tabbat"));
    REQUIRE(s0 != s1);
}

TEST_CASE("clear() resets internal state", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE(b.add("a"));
    REQUIRE(b.add("AA"));
    REQUIRE(b.add("AaA"));
    REQUIRE(b.number() == 6);

    b.clear();
    REQUIRE(b.number() == 0);
    REQUIRE(b.toVector().empty());

    // after clear, should behave like fresh object
    REQUIRE(b.add("bat"));
    REQUIRE(b.add("tab"));
    REQUIRE(b.number() == 2);
}

TEST_CASE("Vector add is atomic: if any invalid, none added", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE(b.add("bat"));
    REQUIRE(b.add("tab"));
    REQUIRE(b.number() == 2);

    // This should fail because of invalid word "a1"
    std::vector<std::string> bad = {"aa", "a1", "bb"};
    REQUIRE_FALSE(b.add(bad));

    // State should be unchanged
    REQUIRE(b.number() == 2);
    auto pals = b.toVector();
    REQUIRE(pals.size() == 2);
}

TEST_CASE("Vector add rejects duplicates within the incoming vector (case-insensitive)", "[FindPalindrome]") {
    FindPalindrome b;

    std::vector<std::string> dup = {"Bat", "tab", "BAT"};
    REQUIRE_FALSE(b.add(dup));

    REQUIRE(b.number() == 0);
    REQUIRE(b.toVector().empty());
}

TEST_CASE("Vector add rejects duplicates against existing words (case-insensitive)", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE(b.add("Bat"));

    std::vector<std::string> v = {"tab", "BAT"}; // BAT duplicates existing Bat
    REQUIRE_FALSE(b.add(v));

    // Still only original state
    REQUIRE(b.toVector().size() == static_cast<size_t>(b.number()));
}

TEST_CASE("cutTest2 pruning doesn't change correctness (basic sanity)", "[FindPalindrome]") {
    FindPalindrome b;

    // A set that should have at least 1 palindrome ordering:
    // "ab" + "ba" -> "abba" or "baab"
    REQUIRE(b.add("ab"));
    REQUIRE(b.add("ba"));
    REQUIRE(b.number() == 2);
}
//cuttest 1 works by checking letter can form a palidrome using counts of letters
//test cuttest1 valid
TEST_CASE("cutTest1: valid palindrome letters", "[cutTest1]") {
    FindPalindrome fp;

    std::vector<std::string> words = {"civic"};

    REQUIRE(fp.cutTest1(words) == true);
}
//test cuttest1 invalid
TEST_CASE("cutTest1: multiple odd counts", "[cutTest1]") {
    FindPalindrome fp;

    std::vector<std::string> words = {"abc"};

    REQUIRE(fp.cutTest1(words) == false);
}
//cuttest1 multiple 
TEST_CASE("cutTest1: multiple strings combine", "[cutTest1]") {
    FindPalindrome fp;

    std::vector<std::string> words = {"ab", "ba"};

    REQUIRE(fp.cutTest1(words) == true);
}
//cuttest 2 fucntions by checking if the letters of 1 vector are in the other "ab" as vec 1 and "abba" as vec 2 would pass
//cuttest 2 valid
TEST_CASE("cutTest2: smaller fits inside larger", "[cutTest2]") {
    FindPalindrome fp;

    std::vector<std::string> v1 = {"ab"};
    std::vector<std::string> v2 = {"abba"};

    REQUIRE(fp.cutTest2(v1, v2) == true);
}
//cuttest 2 invalid
TEST_CASE("cutTest2: insufficient letters", "[cutTest2]") {
    FindPalindrome fp;

    std::vector<std::string> v1 = {"aac"};
    std::vector<std::string> v2 = {"abc"};

    REQUIRE(fp.cutTest2(v1, v2) == false);
}

//room for checkoff
TEST_CASE("CutTest1: checkoff"){
    FindPalindrome fp;

    std::vector<std::string> v1 = {"a","o","aa","ow"};

    REQUIRE(fp.cutTest1(v1) == false);
}