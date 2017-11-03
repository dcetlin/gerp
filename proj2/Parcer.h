/********************
* Daniel Cetlin
* dcetli01
* 20 April 2017
* LinesOfCode.cpp
* Contains definition of Parcer object:
* Given a line of code and an index, Parcer parces through
* the line and hashes each word to a list of all indexes of
* lines with that word. It also hashes the lower case version
* of every word to the possible case variants that are parced.
*********************/
#ifndef PARCER_H
#define PARCER_H

#include "WordHashTemplate.h"
#include "stringProcessing.h"
#include <unordered_set>
#include <vector>
#include <string>

class Parcer
{
public:
	Parcer();
	~Parcer();

	void parce(std::string, int);
	bool find_word(bool, std::string, std::unordered_set<int>&);

private:
	WordHash<std::string> case_i_word_variants;
	WordHash<int> word_index;

	std::string to_lower_case(std::string);
};



#endif