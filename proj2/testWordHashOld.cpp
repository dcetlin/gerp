#include "WordHash.h"
#include <unordered_set>
#include <string>

int main()
{
	WordHash hashtable;
	std::unordered_set<std::string> fruit;
	std::unordered_set<std::string> veg;
	for (int k = 1; k < 1000; k++) {
		//veg.insert(std::to_string(k));
		for (int j = 2; j < 3000; j++) {
		//fruit.insert("p" + std::to_string(k * 2));
			if (j % k == 0 && (j / k < 2 or j + k % k * 2 > k)) {
				hashtable.insert(std::to_string(k), std::to_string(j));
			}
		}
	}		
	hashtable.print();

	if (hashtable.getLinesWith("702", fruit)) {
		std::cout << "KEY: 702:\t"; 
		for (std::string s : fruit)
			std::cout << s << ", ";
		std::cout << std::endl;
	}

	if (hashtable.getLinesWith("578", fruit)) {
		std::cout << "Key: 578:\t"; 
		for (std::string s : fruit)
			std::cout << s << ", ";
		std::cout << std::endl;
	}

	if (hashtable.getLinesWith("731", fruit)) {
		std::cout << "Key: 731:\t"; 
		for (std::string s : fruit)
			std::cout << s << ", ";
		std::cout << std::endl;
	}

	if (hashtable.getLinesWith("4000", fruit)) {
		std::cout << "Key: 731:\t"; 
		for (std::string s : fruit)
			std::cout << s << ", ";
		std::cout << std::endl;
	} else {
		std::cout << "Not found\n";
	}

	return 0;
}