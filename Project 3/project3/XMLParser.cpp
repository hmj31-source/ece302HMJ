#include "XMLParser.hpp"

#include "XMLParser.hpp"

#include <cctype>
#include <stdexcept>

//anonomys so only available in this file
namespace
{
	//removes whitespace from front and end
	std::string trim(const std::string& s)
	{
		//find first nonwhite space char
		size_t start = 0;
		while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start])))
		{
			start++;
		}
		//find last nonwhite space char
		size_t end = s.size();
		while (end > start && std::isspace(static_cast<unsigned char>(s[end-1])))
		{
			end--;
		}
		//return teh substring between start and end
		return s.substr(start, end - start);
	}

	//determines wheter a char is a valid first char of XML tag name
	bool isValidNameStart(char c)
	{
		unsigned char uc = static_cast<unsigned char>(c);
		return std::isalpha(uc) || c == "_" || c ==":";
	}

	//determines whter a char is valid anywhere in an xml tag
	bool isValidNameChar(char c)
	{
		unsigned char uc = static_cast<unsigned char>(c);
		return std::isalnum(uc) || c == "_" || c ==":" || c == "-" ||c == ".";
	}

	//Checks wheter a full string is a valid XML tag name
	bool isValidTagNme(const std::string& name)
	{
		//tag cannot be empty
		if (name.empty())
		{
			return false;
		}

		//Fist char must folloe XML strat-cahr rules
		if (!isValidNameStart(name[0]))
		{
			return false;
		}
		//check every char in the tag name
		for (char c : name)
		{
			if (!isValidNameChar(c))
			{
				return false;
			}
		}

		//all passed return true
		return true;
	}
}

XMLParser::XMLParser()
{
	// TODO
} 

bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	// TODO
	return false;
} 

bool XMLParser::parseTokenizedInput()
{
	// TODO
	return false;
}

void XMLParser::clear()
{
	// TODO
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &inputString) const
{
	// TODO
	return false;
}

int XMLParser::frequencyElementName(const std::string &inputString) const
{
	// TODO
	return -1;
}

