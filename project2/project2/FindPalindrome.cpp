#include <string>
#include <vector>

//added library t oclassify and transfomr single characters
#include <cctype>
//class to report errors
#include <stdexcept>

#include "FindPalindrome.hpp"

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

/** Helper function to convert string to lower case */
static void convertToLowerCase(std::string & value)
{
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i]);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

bool FindPalindrome::isValidWord(const std::string &w)
{
    return false;
}

std::string FindPalindrome::toLowerCopy(const std::string &s)
{
    return std::string();
}

bool FindPalindrome::equalsIgnoreCase(const std::string &a, const std::string &b)
{
    return false;
}

std::string FindPalindrome::concatWords(const std::vector<std::string> &sentence)
{
    return std::string();
}

int FindPalindrome::letterCount(const std::vector<std::string> &v, int counts[26])
{
    return 0;
}

void FindPalindrome::recursiveFindPalindromes(std::vector<std::string>
                                                  candidateSentence,
                                              std::vector<std::string> remainingWords)
{
	// TODO implement this recursive function!
	return;
}

bool FindPalindrome::isPalindrome(std::string testString) const
{
	// make sure that the string is lower case
	convertToLowerCase(testString);
	// see if the characters are symmetric
	int stringLength = testString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (testString[i] != testString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}



//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	// TODO 
	pal = new FindPalindrome();
	cap = 0;
	size = 0;
	words = new std::string[cap];
	numPalidromes = 0;
}

FindPalindrome::~FindPalindrome()
{
	// TODO 
	delete[] pal;
	delete[] words;
	words = nullptr;
	pal = nullptr;
}

int FindPalindrome::number() const
{
	// TODO 
	return numPalidromes;
}

void FindPalindrome::clear()
{
	// TODO 
	delete[] words;
	words = nullptr;
	cap = 0;
	size=0;
	numPalidromes =0;

}

bool FindPalindrome::cutTest1(const std::vector<std::string> & wordVector)
{
	// TODO 
	return false;
}

bool FindPalindrome::cutTest2(const std::vector<std::string> & wordVector1,
                              const std::vector<std::string> & wordVector2)
{
	// TODO 
	return false;
}

bool FindPalindrome::add(const std::string & newWord)
{
	// TODO 
	if (size==cap){
		int newCap = (cap ==0) ? 1:0; cap *2;

		std::string* newWords = new std::string[newCap];
		for (int i = 0; i <size; i++){
			newWords[i] = words[i];
		}
		delete[] words;
		words = newWords;
		cap = newCap;

		words[size++] = newWord;
		return true;
	}

	return false;
}

bool FindPalindrome::add(const std::vector<std::string> & wordVector)
{
	// TODO 
	return false;
}

std::vector< std::vector<std::string> > FindPalindrome::toVector() const
{
	// TODO
	return std::vector< std::vector<std::string> >();
}

