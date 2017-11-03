/********************
* Daniel Cetlin
* dcetli01
* 20 April 2017
* LinesOfCode.cpp
* Contains implimentation of LinesOfCode object
* Uses DirNode and FSTree to navegate a directory and create
* 	a list of all lines of code (path:line: [content]) and sends
*   each line to the Parcer object to process each line and store 
* 	the index of every word
*********************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_set>
#include "LinesOfCode.h"
#include "FSTree.h"
#include "DirNode.h"
#include "Parcer.h"


//Note: only add lines with alphanumeric letters to the vector 
// (save space waste time)

/* default constructor
 * parameters: string */
LinesOfCode::LinesOfCode(std::string directory) : tree(directory)
{
	numElem = 0;
	listOfCode = getAllFiles(tree.getRoot(), "");
}

/* destructor */
LinesOfCode::~LinesOfCode() {}

/* getAllFiles
 * parameters: DirNode*, string
 * return: vector<string>
 * purpose: Parce the tree of directory nodes, produce each string containing
 			path, line, and filename, save each string in a vector, 
 			send each string and index of the vector to the parcer so that
 			the words can be hashed to their indexes in the vector*/
std::vector<std::string> LinesOfCode::getAllFiles
			    (DirNode::DirNode *currDir, std::string full_dir_name)
{
	std::vector<std::string> v;
	full_dir_name += currDir->getName() + "/";
	
	for (int k = 0; k < currDir->numFiles(); k++) {
		std::string filename = currDir->getFile(k);
		std::ifstream inf;
		std::string line;
		openFile(inf, full_dir_name + currDir->getFile(k));
		int numLine = 1;	
		while (!inf.eof()) {
			std::getline(inf, line);
			if (isAlphaNumeric(line)) {
				v.push_back(full_dir_name + currDir->getFile(k)
							+ ":" + std::to_string(numLine) + ": " + line);
				the_parcer.parce(line, numElem++);
			}
			numLine++;
		}
		inf.close();
	}		
	for (int k = 0; k < currDir->numSubDirs(); k++) {
		std::vector<std::string> vSubDirs =
					getAllFiles(currDir->getSubDir(k), full_dir_name);
		v.insert(v.end(), vSubDirs.begin(), vSubDirs.end());
	}
	return v;
}

/* openFile
 * parameters: ifstream&, string
 * return: void
 * purpose: Open a file given a filename check it exists */
void LinesOfCode::openFile(std::ifstream& inf, std::string filename) {
	inf.open(filename.c_str());
	if (!inf.is_open()) {
		std::cerr << "Unable to open " << filename << std::endl;
		exit(1);
	}
}

/* isAlphaNumeric
 * parameters: string
 * return: bool
 * purpose: Returns false if no characters in a line are alphanumeric */
bool LinesOfCode::isAlphaNumeric(std::string s)
{
	for (size_t k = 0; k < s.size(); k++) {
		if (isalnum(s[k]))
			return true;
	}
	return false;
}

/* getLines
 * parameters: unordered_set<int>&
 * return: unordered_set<string>
 * purpose: given a set of indexies, return a set of strings
 			that correspond to each index */
std::unordered_set<std::string> LinesOfCode::getLines
						(const std::unordered_set<int> &indexes)
{
	std::unordered_set<std::string> u_set;
	for (const int i : indexes) {
		u_set.insert(listOfCode[i]);
	}
	return u_set;
}

/* find_word
 * parameters: bool, string, unordered_set<string>&
 * return: bool
 * purpose: search for a word in the lines of code
 			return true if exists and fill given set reference
 			with list of strings */
bool LinesOfCode::find_word(bool is_case_i, std::string word,
					std::unordered_set<std::string> &lines) 
{
	std::unordered_set<int> u_set;
	if (!the_parcer.find_word(is_case_i, word, u_set))
		return false;
	else {
		lines = getLines(u_set);
		return true;
	}

}

/* print (for testing)
 * parameters: none
 * return: void
 * purpose: */
void LinesOfCode::print() {
	for (const std::string s : listOfCode)
		std::cout << s << std::endl;
	std::cout << "NumLines = " << listOfCode.size() << std::endl;
}

/* printWithIndex (for testing)
 * parameters: none
 * return: void
 * purpose: */
void LinesOfCode::printWithIndex() {
	for (size_t k = 0; k < listOfCode.size(); k++)
		std::cout << k << ": " << listOfCode[k] << std::endl;
	std::cout << "NumLines = " << listOfCode.size() << std::endl;
}