/********************
* Daniel Cetlin
* dcetli01
* 20 April 2017
* LinesOfCode.cpp
* Contains definitions of LinesOfCode object
* Uses DirNode and FSTree to navegate a directory and create
* 	a list of all lines of code (path:line: [content]) and sends
*   each line to the Parcer object to process each line and store 
* 	the index of every word
*********************/
#ifndef LINESOFCODE_H
#define LINESOFCODE_H

#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "LinesOfCode.h"
#include "Parcer.h"
#include "FSTree.h"
#include "DirNode.h"

class LinesOfCode
{
public:
	LinesOfCode(std::string);
	~LinesOfCode();
	void print();
	void printWithIndex();
	bool find_word(bool, std::string, std::unordered_set<std::string> &);


private:
	std::vector<std::string> getAllFiles(DirNode::DirNode*, std::string);
	void openFile(std::ifstream&, std::string);
	std::vector<std::string> listOfCode;
	bool isAlphaNumeric(std::string);
	std::unordered_set<std::string> getLines(const std::unordered_set<int> &);
	FSTree tree;
	Parcer the_parcer;
	int numElem;
};




#endif