/********************
* Daniel Cetlin
* dcetli01
* 20 April 2017
* testLinesOfCode.cpp
* tests the LinesOfCode class by printing every line
* of every file found in the given directory
*********************/
#include "LinesOfCode.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		std::cerr << "Usage: ./testLinesOfCode Directory\n";
		return 1;
	}
	std::string directory = argv[1];
	LinesOfCode lines(directory);

	lines.print();

	return 0;
}
