/********************
* Daniel Cetlin
* dcetli01
* 20 April 2017
* GerpSimulation.cpp
* Contains implimentation of object used to simulate gerp
*********************/
#include "Parcer.h"
#include "LinesOfCode.h"
#include "GerpSimulation.h"
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>

/* default constructor
 * parameters: string
 * purpose: initialize simulation object */
GerpSimulation::GerpSimulation(std::string directory) : my_lines(directory){}

/* destructor */
GerpSimulation::~GerpSimulation(){}

/* get_word
 * parameters: bool, string
 * return: void
 * purpose: */
void GerpSimulation::get_word(bool is_case_i, std::string word)
{
	std::unordered_set<std::string> u_set;
	if (my_lines.find_word(is_case_i, word, u_set))
		printList(u_set);
	else if (is_case_i)
		std::cout << " Not Found.\n";
	else
		std::cout << " Not Found. Try with @insensitive or @i.\n";
}

/* printList
 * parameters: unordered_set<string>
 * return: void
 * purpose: print content in unordered_set<string>*/
void GerpSimulation::printList(const std::unordered_set<std::string> &u_set)
{
	for (std::string s : u_set) 
		std::cout << s << std::endl;
}

/* run
 * parameters: none
 * return: void
 * purpose: get a word input from cin and print the lines with that word*/
void GerpSimulation::run()
{
	std::string input;
	while (!std::cin.eof()) {
		std::cout << "Query? ";
		std::cin >> input;
		if (std::cin.eof() or input == Q or input == Q_)
			break;
		else if (input == I or input == I_) {
			std::cin >> input;
			get_word(true, input);
		} else {
			get_word(false, input);
		}
	}
	std::cout << "\nGoodbye! Thank you and have a nice day.\n";
}
