#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "catch.hpp"
#include "XMLParser.hpp"

/* Provided test cases */
TEST_CASE("XMLParser: Test int Stack push and size", "[Stack]")
{
	Stack<int> intStack;
	int testSize = 3;
	int stackSize;
	bool correctPush, correctSize;
	for (int i = 0; i < testSize; i++)
	{
		correctPush = intStack.push(i);
		stackSize = intStack.size();
		correctSize = (stackSize == (i + 1));
		if (!correctPush || !correctSize)
		{
			break;
		}
	}
	REQUIRE(correctPush);
	REQUIRE(correctSize);
}

TEST_CASE("XMLParser: Test int Stack peek, pop", "[Stack]")
{
	Stack<int> intStack;
	int testSize = 10;
	int stackSize;
	bool correctSizeAfterPush;
	for (int i = 0; i < testSize; i++)
	{
		intStack.push(i);
		stackSize = intStack.size();
		correctSizeAfterPush = (stackSize == (i + 1));
		if (!correctSizeAfterPush)
		{
			break;
		}
	}
	REQUIRE(correctSizeAfterPush);
	bool notEmptyYetAfterPop, correctItem, notEmptyYetAfterPeek;
	for (int i = testSize - 1; i >= 0; i--)
	{
		notEmptyYetAfterPop = !intStack.isEmpty();
		int elem = intStack.peek();
		correctItem = (elem == i);
		notEmptyYetAfterPeek = !intStack.isEmpty();
		intStack.pop();
		if (!notEmptyYetAfterPop || !correctItem || !notEmptyYetAfterPeek)
		{
			break;
		}
	}
	REQUIRE(notEmptyYetAfterPop);
	REQUIRE(correctItem);
	REQUIRE(notEmptyYetAfterPeek);
	REQUIRE(intStack.isEmpty() == true);
}


TEST_CASE("XMLParser: Test tokenize <test>stuff</test>", "[XMLParser]")
{
	// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
	XMLParser myXMLParser;
	std::string testString = "<test>stuff</test>";
	REQUIRE(myXMLParser.tokenizeInputString(testString));
	std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
									   TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
									   TokenStruct{StringTokenType::END_TAG, std::string("test")}};
	std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
	REQUIRE(result.size() == output.size());
	bool correctType, correctString;
	for (int i = 0; i < result.size(); i++)
	{
		correctType = (result[i].tokenType == output[i].tokenType);
		correctString = (result[i].tokenString.compare(output[i].tokenString) == 0);
		if (!correctType || !correctString) {
			break;
		}
	}
	REQUIRE(correctType);
	REQUIRE(correctString);
}


TEST_CASE("XMLParser: Test tokenize more elements", "[XMLParser]")
{
	XMLParser myXMLParser;
	std::string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Note src='gmail'>  <From>Tom</From> <To>Alice</To> </Note>";
	REQUIRE(myXMLParser.tokenizeInputString(testString));
	std::vector<TokenStruct> result = {TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
									   TokenStruct{StringTokenType::START_TAG, std::string("Note")},
									   TokenStruct{StringTokenType::START_TAG, std::string("From")},
									   TokenStruct{StringTokenType::CONTENT, std::string("Tom")},
									   TokenStruct{StringTokenType::END_TAG, std::string("From")},
									   TokenStruct{StringTokenType::START_TAG, std::string("To")},
									   TokenStruct{StringTokenType::CONTENT, std::string("Alice")},
									   TokenStruct{StringTokenType::END_TAG, std::string("To")},
									   TokenStruct{StringTokenType::END_TAG, std::string("Note")}};
	std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();

	REQUIRE(result.size() == output.size());
	bool correctType, correctString;
	for (int i = 0; i < result.size(); i++)
	{
		correctType = (result[i].tokenType == output[i].tokenType);
		correctString = (result[i].tokenString.compare(output[i].tokenString) == 0);
		if (!correctType || !correctString) {
			break;
		}
	}
	REQUIRE(correctType);
	REQUIRE(correctString);
}

TEST_CASE("XMLParser: Test parseTokenizedInput", "[XMLParser]")
{
	XMLParser myXMLParser;
	std::string testString = "<test myattr='abcdef'>stuff<this_is_empty_tag/></test>";
	REQUIRE(myXMLParser.tokenizeInputString(testString));
	std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
									   TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
									   TokenStruct{StringTokenType::EMPTY_TAG, std::string("this_is_empty_tag")},
									   TokenStruct{StringTokenType::END_TAG, std::string("test")}};
	std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
	REQUIRE(result.size() == output.size());
	REQUIRE(myXMLParser.parseTokenizedInput());
	output = myXMLParser.returnTokenizedInput();
	REQUIRE(result.size() == output.size());
	bool correctType, correctString;
	for (int i = 0; i < result.size(); i++)
	{
		correctType = (result[i].tokenType == output[i].tokenType);
		correctString = (result[i].tokenString.compare(output[i].tokenString) == 0);
		if (!correctType || !correctString) {
			break;
		}
	}
	REQUIRE(correctType);
	REQUIRE(correctString);
}


TEST_CASE("XMLParser: Test XMLParser parse, contains and frequency", "[XMLParser]")
{
	XMLParser myXMLParser;
	std::ifstream myfile("../TestFile.txt");
	std::string inputString((std::istreambuf_iterator<char>(myfile)), (std::istreambuf_iterator<char>()));

	REQUIRE(myXMLParser.tokenizeInputString(inputString));
	REQUIRE(myXMLParser.parseTokenizedInput());
	REQUIRE(myXMLParser.containsElementName("catalog"));
	REQUIRE(myXMLParser.frequencyElementName("catalog") == 1);
	REQUIRE(myXMLParser.containsElementName("product"));
	REQUIRE(myXMLParser.frequencyElementName("product") == 1);
	REQUIRE(myXMLParser.containsElementName("catalog_item"));
	REQUIRE(myXMLParser.frequencyElementName("catalog_item") == 2);
	REQUIRE(myXMLParser.containsElementName("item_number"));
	REQUIRE(myXMLParser.frequencyElementName("item_number") == 2);
	REQUIRE(myXMLParser.containsElementName("size"));
	REQUIRE(myXMLParser.frequencyElementName("size") == 6);
	REQUIRE(myXMLParser.containsElementName("color_swatch"));
	REQUIRE(myXMLParser.frequencyElementName("color_swatch") == 15);
}

/* Your test cases here */
//XML tokenize test cases
TEST_CASE("Tokenize simple XML", "[XMLParser]")
{
    XMLParser p;

    REQUIRE(p.tokenizeInputString("<test>hello</test>"));

    std::vector<TokenStruct> tokens = p.returnTokenizedInput();

    REQUIRE(tokens.size() == 3);

    REQUIRE(tokens[0].tokenType == START_TAG);
    REQUIRE(tokens[0].tokenString == "test");

    REQUIRE(tokens[1].tokenType == CONTENT);
    REQUIRE(tokens[1].tokenString == "hello");

    REQUIRE(tokens[2].tokenType == END_TAG);
    REQUIRE(tokens[2].tokenString == "test");
}

TEST_CASE("Tokenize empty tag", "[XMLParser]")
{
    XMLParser p;

    REQUIRE(p.tokenizeInputString("<test/>"));

    auto tokens = p.returnTokenizedInput();

    REQUIRE(tokens.size() == 1);
    REQUIRE(tokens[0].tokenType == EMPTY_TAG);
    REQUIRE(tokens[0].tokenString == "test");
}

TEST_CASE("Tokenize declaration", "[XMLParser]")
{
    XMLParser p;

    REQUIRE(p.tokenizeInputString("<?xml version=\"1.0\"?>"));

    auto tokens = p.returnTokenizedInput();

    REQUIRE(tokens.size() == 1);
    REQUIRE(tokens[0].tokenType == DECLARATION);
}

TEST_CASE("Tokenize tag with attributes", "[XMLParser]")
{
    XMLParser p;

    REQUIRE(p.tokenizeInputString("<book id=\"10\">text</book>"));

    auto tokens = p.returnTokenizedInput();

    REQUIRE(tokens.size() == 3);

    REQUIRE(tokens[0].tokenType == START_TAG);
    REQUIRE(tokens[0].tokenString == "book");

    REQUIRE(tokens[1].tokenType == CONTENT);
    REQUIRE(tokens[1].tokenString == "text");

    REQUIRE(tokens[2].tokenType == END_TAG);
    REQUIRE(tokens[2].tokenString == "book");
}

TEST_CASE("Tokenize invalid missing >", "[XMLParser]")
{
    XMLParser p;

    REQUIRE_FALSE(p.tokenizeInputString("<test"));
}

TEST_CASE("Tokenize nested < inside tag", "[XMLParser]")
{
    XMLParser p;

    REQUIRE_FALSE(p.tokenizeInputString("<test <bad>>"));
}

TEST_CASE("Tokenize stray >", "[XMLParser]")
{
    XMLParser p;

    REQUIRE_FALSE(p.tokenizeInputString("hello > world"));
}

TEST_CASE("Tokenize unmatched tags but valid tokens", "[XMLParser]")
{
    XMLParser p;

    REQUIRE(p.tokenizeInputString("<tag>hello"));
}

//additional test cases


//stack tests
//empty on new stack
TEST_CASE("Stack: isEmpty on new stack", "[Stack]")
{
	Stack<int> s;
	REQUIRE(s.isEmpty());
	REQUIRE(s.size() == 0);
}

//pop empty stack
TEST_CASE("Stack: pop on empty stack returns false", "[Stack]")
{
	Stack<int> s;
	REQUIRE_FALSE(s.pop());
	REQUIRE(s.isEmpty());
	REQUIRE(s.size() == 0);
}

//peek empty stack
TEST_CASE("Stack: peek on empty stack throws", "[Stack]")
{
	Stack<int> s;
	REQUIRE_THROWS_AS(s.peek(), std::logic_error);
}

//clear on stack
TEST_CASE("Stack: clear removes all items", "[Stack]")
{
	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);

	REQUIRE_FALSE(s.isEmpty());
	REQUIRE(s.size() == 3);

	s.clear();

	REQUIRE(s.isEmpty());
	REQUIRE(s.size() == 0);
	REQUIRE_FALSE(s.pop());
	REQUIRE_THROWS_AS(s.peek(), std::logic_error);
}

//XML additional tests
//construct on empty
TEST_CASE("XMLParser: constructor starts empty", "[XMLParser]")
{
	XMLParser p;
	std::vector<TokenStruct> tokens = p.returnTokenizedInput();

	REQUIRE(tokens.empty());
}

//clear on empty
TEST_CASE("XMLParser: clear empties token vector after tokenization", "[XMLParser]")
{
	XMLParser p;

	REQUIRE(p.tokenizeInputString("<a>hello</a>"));
	REQUIRE(p.returnTokenizedInput().size() == 3);

	p.clear();

	REQUIRE(p.returnTokenizedInput().empty());
}

//test faild tokeization
TEST_CASE("XMLParser: returnTokenizedInput empty after failed tokenization", "[XMLParser]")
{
	XMLParser p;

	REQUIRE_FALSE(p.tokenizeInputString("<bad"));
	REQUIRE(p.returnTokenizedInput().empty());
}

//trim whitespace only input
TEST_CASE("XMLParser: tokenizeInputString trims whitespace-only input", "[XMLParser]")
{
	XMLParser p;

	REQUIRE_FALSE(p.tokenizeInputString("    \n\t   "));
	REQUIRE(p.returnTokenizedInput().empty());
}

//handeling content
TEST_CASE("XMLParser: tokenizeInputString handles content only", "[XMLParser]")
{
	XMLParser p;

	REQUIRE(p.tokenizeInputString("hello world"));

	std::vector<TokenStruct> tokens = p.returnTokenizedInput();
	REQUIRE(tokens.size() == 1);
	REQUIRE(tokens[0].tokenType == CONTENT);
	REQUIRE(tokens[0].tokenString == "hello world");
}

TEST_CASE("XMLParser: tokenizeInputString ignores whitespace-only content between tags", "[XMLParser]")
{
	XMLParser p;

	REQUIRE(p.tokenizeInputString("<a>   </a>"));

	std::vector<TokenStruct> tokens = p.returnTokenizedInput();
	REQUIRE(tokens.size() == 2);
	REQUIRE(tokens[0].tokenType == START_TAG);
	REQUIRE(tokens[0].tokenString == "a");
	REQUIRE(tokens[1].tokenType == END_TAG);
	REQUIRE(tokens[1].tokenString == "a");
}

TEST_CASE("XMLParser: tokenizeInputString rejects invalid empty tag name", "[XMLParser]")
{
	XMLParser p;

	REQUIRE_FALSE(p.tokenizeInputString("<>"));
	REQUIRE(p.returnTokenizedInput().empty());
}

TEST_CASE("XMLParser: tokenizeInputString rejects invalid end tag spacing", "[XMLParser]")
{
	XMLParser p;

	REQUIRE_FALSE(p.tokenizeInputString("<a></a b>"));
	REQUIRE(p.returnTokenizedInput().empty());
}

TEST_CASE("XMLParser: tokenizeInputString rejects stray greater-than in content", "[XMLParser]")
{
	XMLParser p;

	REQUIRE_FALSE(p.tokenizeInputString("<a>hello > world</a>"));
	REQUIRE(p.returnTokenizedInput().empty());
}

TEST_CASE("XMLParser: tokenizeInputString supports names with underscore dash colon dot", "[XMLParser]")
{
	XMLParser p;

	REQUIRE(p.tokenizeInputString("<a_b-c.d:e></a_b-c.d:e>"));

	std::vector<TokenStruct> tokens = p.returnTokenizedInput();
	REQUIRE(tokens.size() == 2);
	REQUIRE(tokens[0].tokenType == START_TAG);
	REQUIRE(tokens[0].tokenString == "a_b-c.d:e");
	REQUIRE(tokens[1].tokenType == END_TAG);
	REQUIRE(tokens[1].tokenString == "a_b-c.d:e");
}

TEST_CASE("XMLParser: containsElementName throws before tokenize and parse", "[XMLParser]")
{
	XMLParser p;
	REQUIRE_THROWS_AS(p.containsElementName("a"), std::logic_error);
}

TEST_CASE("XMLParser: frequencyElementName throws before tokenize and parse", "[XMLParser]")
{
	XMLParser p;
	REQUIRE_THROWS_AS(p.frequencyElementName("a"), std::logic_error);
}

TEST_CASE("XMLParser: containsElementName throws after tokenize but before parse", "[XMLParser]")
{
	XMLParser p;
	REQUIRE(p.tokenizeInputString("<a></a>"));
	REQUIRE_THROWS_AS(p.containsElementName("a"), std::logic_error);
}

TEST_CASE("XMLParser: frequencyElementName throws after tokenize but before parse", "[XMLParser]")
{
	XMLParser p;
	REQUIRE(p.tokenizeInputString("<a></a>"));
	REQUIRE_THROWS_AS(p.frequencyElementName("a"), std::logic_error);
}

/* These next tests require parseTokenizedInput() to be implemented */

TEST_CASE("XMLParser: parseTokenizedInput returns false on empty token list", "[XMLParser]")
{
	XMLParser p;
	REQUIRE_FALSE(p.parseTokenizedInput());
}

TEST_CASE("XMLParser: containsElementName works after valid parse", "[XMLParser]")
{
	XMLParser p;
	REQUIRE(p.tokenizeInputString("<root><item>one</item><item>two</item></root>"));
	REQUIRE(p.parseTokenizedInput());

	REQUIRE(p.containsElementName("root"));
	REQUIRE(p.containsElementName("item"));
	REQUIRE_FALSE(p.containsElementName("missing"));
}

TEST_CASE("XMLParser: frequencyElementName works after valid parse", "[XMLParser]")
{
	XMLParser p;
	REQUIRE(p.tokenizeInputString("<root><item>one</item><item>two</item></root>"));
	REQUIRE(p.parseTokenizedInput());

	REQUIRE(p.frequencyElementName("root") == 1);
	REQUIRE(p.frequencyElementName("item") == 2);
	REQUIRE(p.frequencyElementName("missing") == 0);
}

TEST_CASE("XMLParser: clear resets parser so contains and frequency throw again", "[XMLParser]")
{
	XMLParser p;
	REQUIRE(p.tokenizeInputString("<root><child></child></root>"));
	REQUIRE(p.parseTokenizedInput());

	REQUIRE(p.containsElementName("root"));
	REQUIRE(p.frequencyElementName("child") == 1);

	p.clear();

	REQUIRE(p.returnTokenizedInput().empty());
	REQUIRE_THROWS_AS(p.containsElementName("root"), std::logic_error);
	REQUIRE_THROWS_AS(p.frequencyElementName("child"), std::logic_error);
}


TEST_CASE("XMLParser: custom", "[XMLParser]")
{
    XMLParser p;
    std::string testString = "<course><name>ECE302</name></course>";

    REQUIRE(p.tokenizeInputString(testString));

    std::vector<TokenStruct> result = {
        TokenStruct{START_TAG, "course"},
		TokenStruct{START_TAG, "name"},
        TokenStruct{CONTENT, "ECE302"},
        TokenStruct{END_TAG, "name"},
		TokenStruct{END_TAG, "course"}
    };

    std::vector<TokenStruct> output = p.returnTokenizedInput();
    REQUIRE(result.size() == output.size());

    for (int i = 0; i < result.size(); i++)
    {
        REQUIRE(result[i].tokenType == output[i].tokenType);
        REQUIRE(result[i].tokenString == output[i].tokenString);
    }

    REQUIRE(p.parseTokenizedInput());
}

TEST_CASE("XMLParser: invalid nesting", "[XMLParser]")
{
    XMLParser p;
    std::string testString = "<a><b></a></b>";

    REQUIRE(p.tokenizeInputString(testString));

    std::vector<TokenStruct> result = {
        TokenStruct{START_TAG, "a"},
        TokenStruct{START_TAG, "b"},
        TokenStruct{END_TAG, "a"},
        TokenStruct{END_TAG, "b"}
    };

    std::vector<TokenStruct> output = p.returnTokenizedInput();
    REQUIRE(result.size() == output.size());

    for (int i = 0; i < result.size(); i++)
    {
        REQUIRE(result[i].tokenType == output[i].tokenType);
        REQUIRE(result[i].tokenString == output[i].tokenString);
    }

    REQUIRE_FALSE(p.parseTokenizedInput());
}

//checkoff
//check this <tag>hello</tag>

TEST_CASE("CHECKOFF", "[XMLParser]"){
	XMLParser p;
	std::string testString = "<tag>hello</tag>";

	REQUIRE(p.tokenizeInputString(testString));

	REQUIRE(p.parseTokenizedInput());
}