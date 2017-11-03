/********************
* Daniel Cetlin
* dcetli01
* 20 April 2017
* testWordHashTemplate.cpp
* tests the WordHashTemplate object by hashing
* strings to lists of strings and strings to lists of ints
*********************/
#include "WordHashTemplate.h"
#include <unordered_set>
#include <string>

void testwithstring();
void testwithint();
void checkfor(WordHash<std::string>&, std::string);
void checkfor(WordHash<int>&, std::string);

int main()
{
	std::cout << "TEST WordHash WITH STRINGS\n";
	testwithstring();
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
			  << "\nTEST WordHash WITH INTS\n";
	testwithint();
	return 0;
}

void testwithstring() {
	std::string keys[] = {"", "Bees", "Pork", "Meat", "Cammle", "Silly",
					  "wonder", "and", "the", "see", "wright", "birds",
					  "!@#$", "what", "why", "who", "till", "at", "when",
					  "poo", "pill", "linguini", "marry", "Susan","Farry",
					  "Rachel", "Jenny", "Beth", "Water", "Cringe", "Ant",
					  "Bee","Annet", "Frangrance", "Till", "Ooops",
					  "Forthelongesttime", "end","WOWBees", "WOWPork",
					  "WOWMeat", "WOWCammle", "WOWSilly", "wonder", "and",
					  "the", "see", "wright", "birds", "!@#$", "what", "why",
					  "who", "till", "at", "WOWwhen", "poo", "pill", "linguini"};

	std::string values[] = {"", "Aaa", "Bbb", "Ccc", "Ddd", "Eee", "Fff",
							"Ggg", "Hhh", "Iii", "Jjj"};
	int sizeKeys = sizeof(keys) / sizeof(std::string);
	int sizeValues = sizeof(values) / sizeof(std::string);

	WordHash<std::string> hashtable;
	for (int k = 1; k < sizeKeys; k++) {
		for (int j = k % sizeValues; j < sizeValues; j += 3)
			hashtable.insert(keys[k], values[j]);
	}		
	hashtable.print();

	checkfor(hashtable, "Ooops");
	checkfor(hashtable, "Bees");
	checkfor(hashtable, "Silly");
	checkfor(hashtable, "Bee");
	checkfor(hashtable, "NotHere");
}

void testwithint()
{
	std::string keys[] = {"", "Bees", "Pork", "Meat", "Cammle", "Silly",
					  "wonder", "and", "the", "see", "wright", "birds",
					  "!@#$", "what", "why", "who", "till", "at", "when",
					  "poo", "pill", "linguini", "marry", "Susan","Farry",
					  "Rachel", "Jenny", "Beth", "Water", "Cringe", "Ant",
					  "Bee","Annet", "Frangrance", "Till", "Ooops",
					  "Forthelongesttime", "end","WOWBees", "WOWPork",
					  "WOWMeat", "WOWCammle", "WOWSilly", "wonder", "and",
					  "the", "see", "wright", "birds", "!@#$", "what", "why",
					  "who", "till", "at", "WOWwhen", "poo", "pill", "linguini"};

	int values[] = {0, 555, 1554, 1324, 66, 190, 1234, 998, 9, 4, 22};
	int sizeKeys = sizeof(keys) / sizeof(std::string);
	int sizeValues = sizeof(values) / sizeof(int);

	WordHash<int> hashtable;
	for (int k = 1; k < sizeKeys; k++) {
		for (int j = k % sizeValues; j < sizeValues; j += 3) {
			hashtable.insert(keys[k], values[j]);
		}
	}		
	hashtable.print();

	checkfor(hashtable, "Ooops");
	checkfor(hashtable, "Bees");
	checkfor(hashtable, "Silly");
	checkfor(hashtable, "Bee");
	checkfor(hashtable, "NotHere");
}


void checkfor(WordHash<std::string> &hashtable, std::string key)
{
	std::unordered_set<std::string> fruit;
	if (hashtable.getLinesWith(key, fruit)) {
		std::cout << "Key: " << key << ":\t"; 
		for (std::string s : fruit)
			std::cout << s << ", ";
		std::cout << std::endl;
	} else 
		std::cout << key << " not found\n";
}

void checkfor(WordHash<int> &hashtable, std::string key)
{
	std::unordered_set<int> fruit;
	if (hashtable.getLinesWith(key, fruit)) {
		std::cout << "Key: " << key << ":\t"; 
		for (int s : fruit)
			std::cout << s << ", ";
		std::cout << std::endl;
	} else 
		std::cout << key << " not found\n";
}