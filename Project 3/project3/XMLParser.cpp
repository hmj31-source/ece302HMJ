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
		while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
			start++;
		}
		//find last nonwhite space char
		size_t end = s.size();
		while (end > start && std::isspace(static_cast<unsigned char>(s[end-1]))) {
			end--;
		}
		//return teh substring between start and end
		return s.substr(start, end - start);
	}

	//determines wheter a char is a valid first char of XML tag name
	bool isValidNameStart(char c)
	{
		unsigned char uc = static_cast<unsigned char>(c);
		return std::isalpha(uc) || c == '_' || c == ':';
	}

	//determines whter a char is valid anywhere in an xml tag
	bool isValidNameChar(char c)
	{
		unsigned char uc = static_cast<unsigned char>(c);
		return std::isalnum(uc) || c == '_' || c == ':' || c == '-' ||c == '.';
	}

	//Checks wheter a full string is a valid XML tag name
	bool isValidTagName(const std::string& name)
	{
		//tag cannot be empty
		if (name.empty()) {
			return false;
		}

		//Fist char must folloe XML strat-cahr rules
		if (!isValidNameStart(name[0])) {
			return false;
		}
		//check every char in the tag name
		for (char c : name) {
			if (!isValidNameChar(c)) {
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
	//initliaze parser by clering all internal data
	clear();
} 

bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	// TODO
	//clear to start
	clear();

	//trim and check if empty if empty fail
	if (trim(inputString).empty()) {
		//if empty return false
		return false;
	}

	//indec to walk through the input string
	size_t i = 0;

	//scan each char untill entire string has been proccessed
	while (i < inputString.size()) {
		//case 1 is start of markup token
		//all XML tags begin <
		if (inputString[i] == '<') {
			//find the closing >
			size_t closePos = inputString.find('>', i +1);
			//if no > return false 
			if (closePos == std::string::npos){
				clear();
				return false;
			}

			//extract between < > 
			std::string inside = inputString.substr(i+1, closePos - i - 1);

			//no nested < inside a tag enclosure
			if (inside.find('<') != std::string::npos){
				clear();
				return false;
			}

			TokenStruct token;
			//case 1a 
			//declaration: <?...?>
			if (inside.size() >= 2 && inside.front() == '?' && inside.back() =='?'){
				//remove ? and trim 
				std::string declText = trim(inside.substr(1, inside.size() - 2));
				//delcaration must contain somehting if not return false
				if (declText.empty()){
					clear();
					return false;
				}
				
				token.tokenType = DECLARATION;
				token.tokenString = declText;
			}
			//case 1b
			//end tag : </name>
			else if (!inside.empty() && inside[0] == '/'){

				//extract the tag name after /
				std::string name = trim(inside .substr(1));

				//no whitespaces allowed inside end tag name
				for ( char c: name){
					if (std::isspace(static_cast<unsigned char>(c))){
						clear();
						return false;
	
					}

				}
				//verify tag name follows XML rules
				if (!isValidTagName(name)){
					clear();
					return false;
				}

				token.tokenType = END_TAG;
				token.tokenString = name;
			}
			//case 1c 
			//start tag or empty tag
			else {
				if (!inside.empty() && std::isspace(static_cast<unsigned char>(inside[0])))
				{
					clear();
					return false;
				}
				//remove leading/trailing whitespace
				std::string tagText = trim(inside);
				bool isEmpty = false;

				//chekc if ends with /
				if (!tagText.empty() && tagText.back() =='/'){
					isEmpty = true;
					//remove / and trim again
					tagText.pop_back();
					tagText = trim(tagText);
				}

				if (tagText.empty()){
					clear();
					return false;
				}

				//extrac only tag name ignore attributes
				size_t j = 0;
				while (j < tagText.size() && !std::isspace(static_cast<unsigned char> (tagText[j]))){
					j++;
				}

				std::string name = tagText.substr(0,j);

				//validate tag name
				if (!isValidTagName(name)){
					clear();
					return false;
				}
				//assigne token type
				token.tokenType = isEmpty ? EMPTY_TAG : START_TAG;
				token.tokenString = name;
			}

			//save generated token
			tokenizedInputVector.push_back(token);
			//continue search after closing >
			i = closePos +1;
		}
		//case 2 A > encountered outsie a tag
		else if (inputString[i] == '>'){
			//stray >
			clear();
			return false;
		}
		//case 3 content between tags
		else{
			//find next oppening tag
			size_t nextOpen = inputString.find('<', 1);
			std::string content;

			//if noe more tags exist, everthing remaining is content
			if (nextOpen == std::string::npos){
				content = inputString.substr(i);
				i = inputString.size();
			}
			//extract content between current position and next tag
			else{
				content = inputString.substr(i,nextOpen - i);
				i = nextOpen;
			}

			//reject a stray > in content
			if (content.find('>') != std::string::npos){
				clear();
				return false;
			}
			//remove witespace
			std::string trimmedContent = trim(content);

			//only store content if it isn't whitespace
			if (!trimmedContent.empty()){
				TokenStruct token;
				token.tokenType = CONTENT;
				token.tokenString = trimmedContent;
				tokenizedInputVector.push_back(token);
			}
		}
	}
	//tokenization succesgull
	tokenizedOK = true;
	//parsing has not occured
	parsedOK = false;

	return true; 
} 

bool XMLParser::parseTokenizedInput()
{
	// TODO
	return false;
}

void XMLParser::clear()
{
	// TODO
	//clear input vector
	tokenizedInputVector.clear();
	//clear element name bag
	elementNameBag.clear();
	//clear stack
	parseStack.clear();
	//set my private vars to false
	tokenizedOK = false;
	parsedOK = false;
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &inputString) const
{
	// TODO
	//check if it parsed and tokenized okay
	if (!tokenizedOK || !parsedOK) throw std::logic_error("XML input has not been succesfully tokenized and parsed");

	//returns true if the name is in the bag
	return elementNameBag.contains(inputString);
}

int XMLParser::frequencyElementName(const std::string &inputString) const
{
	// TODO
	//check if parsed and tokenized
	if (!tokenizedOK || !parsedOK) throw std::logic_error("XML input has not been succesfully tokenized and parsed");

	return elementNameBag.getFrequencyOf(inputString);
}

