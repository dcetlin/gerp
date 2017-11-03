/********************
* Daniel Cetlin
* dcetli01
* 13 April 2017
* FSTreeTraversal.cpp
* Prints all filenames from directory givin in command line
*********************/
#include "FSTree.h"
#include "DirNode.h"
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> getAllFiles(DirNode*, std::string);
void printDirectory(FSTree);

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		std::cerr << "Usage: ./treeTraversal Directory\n";
		return 1;
	}
	std::string directory = argv[1];
	FSTree tree(directory);
	printDirectory(tree);

	return 0;
}
/* printDirectory
 * Parameters: FSTree
 * Returns: void
 * Purpose: Print all files in given tree*/
void printDirectory(FSTree tree) {
	std::vector<std::string> v = getAllFiles(tree.getRoot(), "");
	for (const std::string s : v)
		std::cout << s << std::endl;
}

/* getAllFiles
 * Parameters: DirNode, string
 * Returns: vector<string>
 * Purpose: Recursively parces tree and returns a vector containing
 *          all filenames (string) in proper format               */
std::vector<std::string> getAllFiles(DirNode::DirNode *currDir,
										std::string full_dir_name)
{
	std::vector<std::string> v;
	full_dir_name += currDir->getName() + "/";
	
	for (int k = 0; k < currDir->numFiles(); k++) 
		v.push_back(full_dir_name + currDir->getFile(k));
	
	for (int k = 0; k < currDir->numSubDirs(); k++) {
		std::vector<std::string> vSubDirs =
					getAllFiles(currDir->getSubDir(k), full_dir_name);
		v.insert(v.end(), vSubDirs.begin(), vSubDirs.end());
	}
	return v;
}