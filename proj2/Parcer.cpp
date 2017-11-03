/********************
* Daniel Cetlin
* dcetli01
* 20 April 2017
* LinesOfCode.cpp
* Contains implimentation of Parcer object
* Given a line of code and an index, Parcer parces through
* the line and hashes each word to a list of all indexes of
* lines with that word. It also hashes the lower case version
* of every word to the possible case variants that are parced.
*********************/
#include "WordHashTemplate.h"
#include "stringProcessing.h"
#include "Parcer.h"
#include <unordered_set>
#include <vector>
#include <string>
#include <sstream>

/* Constructor/Destructor */
Parcer::Parcer(){}
Parcer::~Parcer(){}

/* parce
 * parameters: string, int
 * return: void
 * purpose: stream a line and parce every word. Add each word to
 			a heap for lowercase word to word and word to index */
void Parcer::parce(std::string line, int index)
{
	std::string word;
	std::stringstream ss(line);
	while (ss >> word) {
		word = stripNonAlphaNum(word);
		if (word != "") {
			word_index.insert(word, index);
			case_i_word_variants.insert(to_lower_case(word), word);
		}
	}
}

/* to_lower_case
 * parameters: string
 * return: string
 * purpose: take a string and return the lower case version of that string */
std::string Parcer::to_lower_case(std::string s)
{
	for (size_t k = 0; k < s.size(); k++) {
		s[k] = tolower(s[k]);
	}
	return s;
}

/* find_word
 * parameters: bool, string, unordered_set<int>&
 * return: bool
 * purpose: if word exists in hash (case sensitive or case insensitive)
 			set given unordered_set indexes to the list of indexes
 			that contain that word */
bool Parcer::find_word(bool is_case_i, std::string word,
					std::unordered_set<int> &indexes) 
{
	word = stripNonAlphaNum(word);
	if (is_case_i) {
		std::unordered_set<std::string> allwords;
		if (word == "" or 
			!case_i_word_variants.getLinesWith(to_lower_case(word), allwords))
			return false;
		else {
			std::unordered_set<int> lineNums;
			for (std::string s : allwords) {
				word_index.getLinesWith(s, lineNums);
				indexes.insert(lineNums.begin(), lineNums.end());
			}
		}
	} else {
		if (!word_index.getLinesWith(word, indexes))
			return false;
	}
	return true;
}