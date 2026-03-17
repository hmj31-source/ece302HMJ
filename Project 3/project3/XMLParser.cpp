#include "XMLParser.hpp"

#include <cctype>
#include <stdexcept>

// anonymous namespace so helper functions are only visible in this file
namespace
{
	// remove whitespace from the front and end of a string
	std::string trim(const std::string& s)
	{
		size_t start = 0;
		while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start])))
		{
			start++;
		}

		size_t end = s.size();
		while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
		{
			end--;
		}

		return s.substr(start, end - start);
	}

	// checks whether a character is valid as the FIRST character of an XML tag name
	bool isValidNameStart(char c)
	{
		unsigned char uc = static_cast<unsigned char>(c);
		return std::isalpha(uc) || c == '_' || c == ':';
	}

	// checks whether a character is valid anywhere in an XML tag name
	bool isValidNameChar(char c)
	{
		unsigned char uc = static_cast<unsigned char>(c);
		return std::isalnum(uc) || c == '_' || c == ':' || c == '-' || c == '.';
	}

	// checks whether an entire string is a valid XML tag name
	bool isValidTagName(const std::string& name)
	{
		// tag name cannot be empty
		if (name.empty())
		{
			return false;
		}

		// first character must be valid
		if (!isValidNameStart(name[0]))
		{
			return false;
		}

		// every character must be valid
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
	// initialize parser by clearing all internal data
	clear();
}

bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	// always start fresh
	clear();

	// if the input is all whitespace, tokenization fails
	if (trim(inputString).empty())
	{
		return false;
	}

	size_t i = 0;

	// scan through the whole input string
	while (i < inputString.size())
	{
		// CASE 1: found start of markup '<'
		if (inputString[i] == '<')
		{
			// find matching closing '>'
			size_t closePos = inputString.find('>', i + 1);
			if (closePos == std::string::npos)
			{
				clear();
				return false;
			}

			// get text between < and >
			std::string inside = inputString.substr(i + 1, closePos - i - 1);

			// nested '<' inside a tag is invalid
			if (inside.find('<') != std::string::npos)
			{
				clear();
				return false;
			}

			TokenStruct token;

			// CASE 1A: declaration <? ... ?>
			if (inside.size() >= 2 && inside.front() == '?' && inside.back() == '?')
			{
				std::string declText = trim(inside.substr(1, inside.size() - 2));

				// declaration must contain something
				if (declText.empty())
				{
					clear();
					return false;
				}

				token.tokenType = DECLARATION;
				token.tokenString = declText;
			}

			// CASE 1B: end tag </name>
			else if (!inside.empty() && inside[0] == '/')
			{
				if (inside.find('\n') != std::string::npos ||
					inside.find('\r') != std::string::npos ||
					inside.find('\t') != std::string::npos)
				{
					clear();
					return false;
				}
				std::string name = trim(inside.substr(1));

				// end tag name cannot contain whitespace
				for (char c : name)
				{
					if (std::isspace(static_cast<unsigned char>(c)))
					{
						clear();
						return false;
					}
				}

				// end tag name must be valid
				if (!isValidTagName(name))
				{
					clear();
					return false;
				}

				token.tokenType = END_TAG;
				token.tokenString = name;
			}

			// CASE 1C: start tag <name> or empty tag <name/>
			else
			{
				// reject whitespace immediately after '<'
				if (!inside.empty() && std::isspace(static_cast<unsigned char>(inside[0])))
				{
					clear();
					return false;
				}

				// reject embedded newlines/tabs in tag markup
				if (inside.find('\n') != std::string::npos ||
					inside.find('\r') != std::string::npos ||
					inside.find('\t') != std::string::npos)
				{
					clear();
					return false;
				}

				std::string tagText = trim(inside);
				bool isEmpty = false;

				// check for empty tag
				if (!tagText.empty() && tagText.back() == '/')
				{
					isEmpty = true;
					tagText.pop_back();
					tagText = trim(tagText);
				}

				if (tagText.empty())
				{
					clear();
					return false;
				}

				// extract tag name only, ignore attributes
				size_t j = 0;
				while (j < tagText.size() &&
					   !std::isspace(static_cast<unsigned char>(tagText[j])))
				{
					j++;
				}

				std::string name = tagText.substr(0, j);

				// validate extracted tag name
				if (!isValidTagName(name))
				{
					clear();
					return false;
				}

				token.tokenType = isEmpty ? EMPTY_TAG : START_TAG;
				token.tokenString = name;
			}

			// save token and continue after '>'
			tokenizedInputVector.push_back(token);
			i = closePos + 1;
		}

		// CASE 2: stray '>' outside a tag is invalid
		else if (inputString[i] == '>')
		{
			clear();
			return false;
		}

		// CASE 3: content between tags
		else
		{
			size_t nextOpen = inputString.find('<', i);
			std::string content;

			// if there are no more tags, rest is content
			if (nextOpen == std::string::npos)
			{
				content = inputString.substr(i);
				i = inputString.size();
			}
			else
			{
				// extract content up to next tag
				content = inputString.substr(i, nextOpen - i);
				i = nextOpen;
			}

			// stray '>' inside content is invalid
			if (content.find('>') != std::string::npos)
			{
				clear();
				return false;
			}

			// ignore pure whitespace content
			std::string trimmedContent = trim(content);
			if (!trimmedContent.empty())
			{
				TokenStruct token;
				token.tokenType = CONTENT;
				token.tokenString = trimmedContent;
				tokenizedInputVector.push_back(token);
			}
		}
	}

	// tokenization succeeded
	tokenizedOK = true;
	parsedOK = false;
	return true;
}

bool XMLParser::parseTokenizedInput()
{
	// cannot parse unless tokenization succeeded and tokens exist
	if (!tokenizedOK || tokenizedInputVector.empty())
	{
		return false;
	}

	// start parsing fresh
	parseStack.clear();
	elementNameBag.clear();
	parsedOK = false;

	bool seenRoot = false;    // have we seen the root element yet?
	bool rootClosed = false;  // has the root element finished?

	for (const TokenStruct& token : tokenizedInputVector)
	{
		switch (token.tokenType)
		{
			case DECLARATION:
				// declarations are only allowed before the root element
				if (seenRoot || rootClosed)
				{
					return false;
				}
				break;

			case CONTENT:
				// content must be inside an open element
				if (parseStack.isEmpty())
				{
					return false;
				}
				break;

			case START_TAG:
				// cannot start a new element after the root is already closed
				if (rootClosed)
				{
					return false;
				}

				// first start tag becomes the root
				if (!seenRoot)
				{
					seenRoot = true;
				}
				// if stack is empty here, that means we are trying to start
				// a second top-level root element
				else if (parseStack.isEmpty())
				{
					return false;
				}

				// push open tag name and store it in bag
				parseStack.push(token.tokenString);
				elementNameBag.add(token.tokenString);
				break;

			case EMPTY_TAG:
				// empty tag cannot appear after root already closed
				if (rootClosed)
				{
					return false;
				}

				// store element name in bag
				elementNameBag.add(token.tokenString);

				// if this is the first element, it is the root and it closes immediately
				if (!seenRoot)
				{
					seenRoot = true;
					rootClosed = true;
				}
				// if stack is empty and we already saw a root, this is a second top-level root
				else if (parseStack.isEmpty())
				{
					return false;
				}
				break;

			case END_TAG:
				// cannot close a tag if nothing is open
				if (parseStack.isEmpty())
				{
					return false;
				}

				// end tag must match most recent open start tag
				if (parseStack.peek() != token.tokenString)
				{
					return false;
				}

				parseStack.pop();

				// if stack becomes empty, the root has finished
				if (parseStack.isEmpty())
				{
					rootClosed = true;
				}
				break;
		}
	}

	// valid XML must have:
	// - seen a root
	// - root closed
	// - no unclosed tags left
	if (!seenRoot || !rootClosed || !parseStack.isEmpty())
	{
		return false;
	}

	parsedOK = true;
	return true;
}

void XMLParser::clear()
{
	// clear all internal data structures
	tokenizedInputVector.clear();
	elementNameBag.clear();
	parseStack.clear();

	// reset parser state flags
	tokenizedOK = false;
	parsedOK = false;
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &inputString) const
{
	// these functions only work after successful tokenize + parse
	if (!tokenizedOK || !parsedOK)
	{
		throw std::logic_error("XML input has not been succesfully tokenized and parsed");
	}

	return elementNameBag.contains(inputString);
}

int XMLParser::frequencyElementName(const std::string &inputString) const
{
	// these functions only work after successful tokenize + parse
	if (!tokenizedOK || !parsedOK)
	{
		throw std::logic_error("XML input has not been succesfully tokenized and parsed");
	}

	return elementNameBag.getFrequencyOf(inputString);
}