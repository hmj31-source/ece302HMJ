#include "XMLParser.hpp"

#include "XMLParser.hpp"

#include <cctype>
#include <stdexcept>

namespace
{
	std::string trim(const std::string& s)
	{
		size_t start = 0;
		while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start])))
		{
			start++;
		}

		size_t end = s.size();
		while (end > start && std::isspace(static_cast<unsigned char>(s[end-1])))
		{
			end--;
		}

		return s.substr(start, end - start);
	}

	bool isValidNameStart(char c)
	{
		unsigned char uc = static_cast<unsigned char>(c);
		return std::isalpha(uc) || c == "_" || c ==":";
	}

	bool isValidNameChar(char c)
	{
		unsigned char uc = static_cast<unsigned char>(c);
		return std::isalnum(uc) || c == "_" || c ==":" || c == "-" ||c == ".";
	}
	bool isValidTagNme(const std::string& name)
	{
		if (name.empty())
		{
			return false;
		}

		if (!isValidNameStart(name[0]))
		{
			return false;
		}

		for (char c : name)
		{
			if (!isValidNameChar(c))
			{
				return false;
			}
		}
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

