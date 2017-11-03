/********************
* Daniel Cetlin
* dcetli01
* 13 April 2017
* stringProcessing.h
* Contains implimentation for strip
*********************/

#include <string>
#include "stringProcessing.h"

/* strip
 * Parameters: string
 * Returns: string
 * Purpose: Return given string with all edge
 * non-alphanumeric characters removed */
std::string stripNonAlphaNum(std::string s)
{
	std::string newS = "";
	size_t start = 0, end = 0;
	for (size_t k = 0; k < s.size(); k++) {
		if (isalnum(s[k])) {
			start = k;
			break;
		}
	}
	for (size_t k = s.size() - 1; (k+1) > 0; k--) {
		if (isalnum(s[k])) {
			end = k + 1;
			break;
		}
	}
	return s.substr(start, end - start);
}