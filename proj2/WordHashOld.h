#ifndef WORDHASH_H
#define WORDHASH_H

#include <unordered_set>
#include <vector>
#include <functional>
#include <string>
#include <iostream>

//template <typename ElemType>

typedef std::unordered_set<std::string> ValueType;
typedef std::string KeyType;

class WordHash{

public:
	WordHash();
	~WordHash();
	WordHash(WordHash&&);
	//void parse(std::string, int);
	bool getLinesWith(const KeyType&, ValueType&);
	void insert(KeyType, std::string);
	void print();

	
private:
	struct LinkNode {
		KeyType key;
		ValueType value;
		LinkNode* next;
	};

	LinkNode** newTable(int);
	void deleteList(LinkNode *node);
	bool findKey(LinkNode*, KeyType, LinkNode*&);
	void expand();
	void insert(LinkNode*, LinkNode**);
	LinkNode* getLast(LinkNode*);


	LinkNode** table; //

	const int INITIAL_CAPACITY = 100;
	const float INCREASE_THREASHOLD = .7;
	int capacity;
	int numElem;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

WordHash::WordHash()
{
	table = newTable(INITIAL_CAPACITY);
	numElem = 0;
}

WordHash::~WordHash()
{
	for (int k = 0; k < capacity; k++) {
		if (table[k] != NULL)
			deleteList(table[k]);
	}
	delete [] table;
}

WordHash::WordHash(WordHash&& other)
{
	capacity = other.capacity;
	numElem = other.numElem;
	table = other.table;

	other.capacity = other.numElem = 0;
	for (int k = 0; k < capacity; k++) 
		other.table[k] = NULL;
	other.table = NULL;
}

void WordHash::deleteList(LinkNode *node)
{
        if (node != NULL) {
            deleteList(node->next);
            delete node;
        }
}

WordHash::LinkNode** WordHash::newTable(int newSize)
{
	LinkNode** temp = new LinkNode*[newSize];
	capacity = newSize;
	for (int k = 0; k < newSize; k++)
		temp[k] = NULL;
	return temp;
}

static size_t hashFunction(KeyType key)
{
	return std::hash<KeyType>{}(key);
}

void WordHash::insert(KeyType key, std::string word)
{
        expand();
        size_t index = hashFunction(key) % capacity;
        LinkNode *temp = table[index];
  		if (findKey(table[index], key, temp)) {
        	table[index]->value.insert(word);
       	} else {
        	LinkNode *insert = new LinkNode;
        	insert->key = key;
        	insert->value.insert(word);
        	insert->next = NULL;
        	if (table[index] == NULL)
        		table[index] = insert;
        	else {
        		//std::cout << "Key: " << temp->key << "->next@index " << index << " = " << key << std::endl;
        		temp->next = insert;
        	}
        	numElem++;
    	}	

        	//std::cout << "[KEY: " << key;
			//std::cout << " at index " << index << std::endl;
}

bool WordHash::findKey(LinkNode* curr, KeyType key, LinkNode* &find)
{
	if (curr == NULL)
		return false;
	else if (curr->key == key) {
		find = curr;
		return true;
	} else {
		//std::cout << curr->key << " Not null or the key\n";
		find = curr;
		return findKey(curr->next, key, find);
	}
}

WordHash::LinkNode* WordHash::getLast(LinkNode* curr)
{
    if (curr->next != NULL)
        getLast(curr->next);
    return curr;
}

void WordHash::expand()
{
        if ((float(numElem) / float(capacity)) <= INCREASE_THREASHOLD)
            return;

        capacity *= 2;
        LinkNode** tempBiggerTable = newTable(capacity);

        for (int k = 0; k < capacity / 2; k++) {
            if (table[k] != NULL) {
                LinkNode* temp = table[k];
                LinkNode* next;
                do {
                	next = temp->next;
               		insert(temp, tempBiggerTable);
               		temp = next;
            	} while (temp != NULL);
            }
        }

        delete [] table;
        table = tempBiggerTable;
}

void WordHash::insert(LinkNode* node, LinkNode** tempTable)
{
  		size_t index = hashFunction(node->key) % capacity;
  		
  		if (tempTable[index] == NULL) {
        	tempTable[index] = node;
       	} else {
        	LinkNode* temp = tempTable[index];
        	while (temp->next != NULL)
        		temp = temp->next;
        	temp->next = node;
    	}
    	node->next = NULL;
}

bool WordHash::getLinesWith(const KeyType& key, ValueType& list) 
{
	LinkNode *bucket = table[hashFunction(key) % capacity];
	LinkNode *temp = NULL;
	if (bucket == NULL)
		return false;
	if (findKey(bucket, key, temp)) {
        list = temp->value;
        return true;
    } else {
    	return false;
	}
}

void WordHash::print()
{
	int count = 0;
	for (int k = 0; k < capacity; k++) {
		LinkNode* ln = table[k];
		if (ln != NULL) {
			LinkNode* temp = ln;
			std::cout << k << ":\t";
			do {
				count++;
				std::cout << "[KEY: " << temp->key;
				std::cout << " {";
				for (std::string s : temp->value)
					std::cout << s << ", ";
				std::cout << "} ] -> ";
				temp = temp->next;
			} while (temp != NULL);
			std::cout << "NULL" << std::endl;
		} else {
			std::cout << k << ":\t EMPTY" << std::endl;
		}
	}
	std::cout << count << " KEY's printed\n" << numElem << " elements\n";
}


#endif
