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
	//check if the string is empty
	if (w.empty()) return false;
	//for length of the w string
	for (unsigned char c : w) {
		//check if char is n alphabet return false if not
		if (!std::isalpha(c)) return false;
	}
	//retur ntrue if passes first case. 
    return true;
}

//lower case function
std::string FindPalindrome::toLowerCopy(const std::string &s)
{
	//output string defined
	std::string out = s;
	//for length of outstring convert to lower using cctype library
	for (char& c: out) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    //return the stirng
	return out;;
}

bool FindPalindrome::equalsIgnoreCase(const std::string &a, const std::string &b)
{
	//check if the two strings are the same and return true or false
    return toLowerCopy(a) == toLowerCopy(b);
}

std::string FindPalindrome::concatWords(const std::vector<std::string> &sentence)
{
	//string varible to return 
	std::string s;
	// range based over a vector for loop
	for (const auto& w : sentence) s += w; // combine s and w
    //return varible
	return s;
}

int FindPalindrome::letterCount(const std::vector<std::string> &v, int counts[26])
{
	//intializes all letter counts to zero
	for (int i =0; i< 26; i++) counts[i] = 0;
	//declare total
	int total = 0;
	//loop thorugh loop thorugh words range over the vector
	for (const auto& w: v){
		//lop characters
		for (unsigned char c: w) {
			//lowercase normalize
			char lc = static_cast<char>(std::tolower(c));
			//alphabet check
			if (lc >= 'a' && lc <= 'z'){
				//increment at that letter
				counts[lc - 'a']++;
				//increase total
				total++;
			}
		}
	}
    return total;
}

void FindPalindrome::recursiveFindPalindromes(std::vector<std::string>
                                                  candidateSentence,
                                              std::vector<std::string> remainingWords)
{
	// TODO implement this recursive function!
	//cut tests
	if (!cutTest2(candidateSentence, remainingWords)) return;

	//base case
	if (remainingWords.empty()) {
		//is palindrome helper call and call concat helper
		if (isPalindrome(concatWords(candidateSentence))) {
			//add to palidrome sentences
			m_palSentences.push_back(candidateSentence);
		}
		return;
	}
	//if not empty check for palindromes
	for (size_t i =0 ; i< remainingWords.size(); i++){
		auto nextCandidate = candidateSentence;
		nextCandidate.push_back(remainingWords[i]);

		auto nextRemaining = remainingWords;
		nextRemaining.erase(nextRemaining.begin() + static_cast<long>(i));

		recursiveFindPalindromes(nextCandidate, nextRemaining);
	}
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
	//vectors start empty
}

FindPalindrome::~FindPalindrome()
{
	// TODO 
	//nothing to delete
}

int FindPalindrome::number() const
{
	// TODO 
	return static_cast<int>(m_palSentences.size());
}

void FindPalindrome::clear()
{
	// TODO 
	m_words.clear();
	m_palSentences.clear();

}

bool FindPalindrome::cutTest1(const std::vector<std::string> & wordVector)
{
	// TODO 
	//alphabet array
	int counts[26];
	//call count helper
	letterCount(wordVector, counts);
	//declare odd intiger
	int odd = 0;
	//loop over every letter
	for (int i = 0; i < 26; i++) {
		//check if the count can be divided by 2 evenly
		if (counts[i] % 2!= 0) odd++; // add to odd if it has remainder
		//if a letter is odd return false
		if (odd > 1) return false;
	}
	//else return true
	return true;
}

bool FindPalindrome::cutTest2(const std::vector<std::string> & wordVector1,
                              const std::vector<std::string> & wordVector2)
{
	// TODO 
	//letter count for both vectors
	int c1[26], c2[26];
	//lenght 2 = total count of each letter
	int len1 = letterCount(wordVector1, c1);
	int len2 = letterCount(wordVector2, c2);

	//determine smaller side
	const int* small = (len1 <= len2) ? c1 : c2;
	const int* large = (len1 <= len2) ? c2: c1;
	//iterate thorugh every letter
	for (int i = 0; i < 26; i++) {
		//check if the smaller side needs more of a letter than larger side
		if (small[i] > large[i]) return false;
	}
	//return true if passes. 
	return true;
}

bool FindPalindrome::add(const std::string & newWord)
{
	// TODO 
	//check if it is a valid work
	if (!isValidWord(newWord)) return false;

	for ( const auto& w : m_words) {
		if (equalsIgnoreCase(w, newWord)) return false;
	}
	m_words.push_back(newWord);

	//recompute 
	//clear plaidrome sentince array
	m_palSentences.clear();
	//check the cut test and if it false return true
	if (!cutTest1(m_words)) return true;

	//call recursive palindrome
	recursiveFindPalindromes({}, m_words);

	return true;
}


bool FindPalindrome::add(const std::vector<std::string> & wordVector)
{
	// TODO 
	//validate all words
	for (const auto& w: wordVector)
		if (!isValidWord(w)) return false;

	//duplicates within vector
	for (size_t i = 0; i < wordVector.size(); i++) {
		for (size_t j = i + 1; j < wordVector.size(); j++){
			if (equalsIgnoreCase(wordVector[i], wordVector[j])) return false;
		}
	}

	//duplicates vs existing
	for (const auto& nw : wordVector){
		for (const auto& ow : m_words){
			if (equalsIgnoreCase(nw,ow)) return false;
		}
	}

	//comit
	for (const auto& w: wordVector) m_words.push_back(w);
	//recompute
	m_palSentences.clear();
	if (!cutTest1(m_words)) return true;

	//call recursive fucntion. 
	recursiveFindPalindromes({}, m_words);
	return true;
}

std::vector< std::vector<std::string> > FindPalindrome::toVector() const
{
	// TODO
	//return the vector
	return m_palSentences;
}

