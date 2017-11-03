/********************
* Daniel Cetlin
* dcetli01
* 20 April 2017
* GerpSimulation.h
* Contains definitions of object used to simulate gerp
*********************/
#ifndef GERPSIMULATION_H
#define GERPSIMULATION_H

#include "Parcer.h"
#include "LinesOfCode.h"
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>

class GerpSimulation
{
public:
	GerpSimulation(std::string);
	~GerpSimulation();
	void run();

private:
	Parcer my_parcer;
	LinesOfCode my_lines;
	void get_word(bool, std::string);
	void printList(const std::unordered_set<std::string> &);

	const std::string Q = "@q";
	const std::string Q_ = "@quit";
	const std::string I = "@i";
	const std::string I_ = "@insensitive";
};

#endif
