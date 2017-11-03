/********************
* Daniel Cetlin
* dcetli01
* 20 April 2017
* testStringProcessing.cpp
* tests the stripNonAlphaNum function
*********************/
#include "stringProcessing.h"
#include <iostream>
using namespace std;

int main()
{
	string s1("Hello# 1 #World");
	string s2("Hello# 2 #World!");
	string s3("Hello# 3 #World!!!!!");
	string s4("!Hello# 4 #World");
	string s5("!!!!!Hello# 5 #World!");
	string s6("!!!!!Hello# 6 #World!!!!!");

	cout << stripNonAlphaNum(s1) << " | " << stripNonAlphaNum(s2)
		 << " | " << stripNonAlphaNum(s3) << "\n" << stripNonAlphaNum(s4)
		 << " | " << stripNonAlphaNum(s5) << " | " << stripNonAlphaNum(s6) << endl;

	string s;
	cout << "Type word to strip: ";
	cin >> s;
	cout << stripNonAlphaNum(s) << endl;
	return 0;
}
