/********************
* Daniel Cetlin
* dcetli01
* 20 April 2017
* LinesOfCode.cpp
* Contains .cpp main function to run the gerp simulation
*********************/
#include "GerpSimulation.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		std::cerr << "Usage:  gerp directory\n"
			 << "            where:  directory is a valid directory\n";
		return 1;
	}
	GerpSimulation sim((std::string(argv[1])));
	sim.run();
	return 0;
}