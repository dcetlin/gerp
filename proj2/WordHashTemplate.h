/********************
* Daniel Cetlin
* dcetli01
* 20 April 2017
* WordHashTemplate.h
* Contains definitions and implimentation of WordHash
* Hashes string keys to values which are unordred sets of
* either strings or ints.
*********************/
#ifndef WORDHASH_H
#define WORDHASH_H

#include <unordered_set>
#include <vector>
#include <functional>
#include <string>
#include <iostream>



typedef std::string KeyType;

template <typename ElemType>
using ValueType = std::unordered_set<ElemType>;

template <typename ElemType>
class WordHash{

public:
	WordHash();
	~WordHash();
	WordHash(WordHash&&);
	bool getLinesWith(const KeyType&, ValueType<ElemType>&);
	void insert(KeyType, ElemType);
	void print();

	
private:
	struct LinkNode {
		KeyType key;
		ValueType<ElemType> value;
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

/* constructor */
template<typename ElemType>
WordHash<ElemType>::WordHash()
{
	table = newTable(INITIAL_CAPACITY);
	numElem = 0;
}

/* destructor */
template<typename ElemType>
WordHash<ElemType>::~WordHash()
{
	for (int k = 0; k < capacity; k++) {
		if (table[k] != NULL)
			deleteList(table[k]);
	}
	delete [] table;
}

/* Move constructor (not used)
 * parameters: WordHash&& */
template<typename ElemType>
WordHash<ElemType>::WordHash(WordHash&& other)
{
	capacity = other.capacity;
	numElem = other.numElem;
	table = other.table;

	other.capacity = other.numElem = 0;
	for (int k = 0; k < capacity; k++) 
		other.table[k] = NULL;
	other.table = NULL;
}

/* deleteList
 * parameters: LinkNode*
 * return: void
 * purpose: delete all nodes in a linked list */
template<typename ElemType>
void WordHash<ElemType>::deleteList(LinkNode *node)
{
        if (node != NULL) {
            deleteList(node->next);
            delete node;
        }
}

/* newTable
 * parameters: int
 * return: LinkNode**
 * purpose: create a table of given size and return the table */
template<typename ElemType>
typename WordHash<ElemType>::LinkNode** WordHash<ElemType>::newTable(
														 int newSize)
{
	LinkNode** temp = new LinkNode*[newSize];
	capacity = newSize;
	for (int k = 0; k < newSize; k++)
		temp[k] = NULL;
	return temp;
}

/* hashFunction
 * parameters: KetType
 * return: size_t
 * purpose: return index for hashed key */
static size_t inline hashFunction(KeyType key)
{
	return std::hash<KeyType>{}(key);
}

/* insert
 * parameters: KeyType, ElemType
 * return: void
 * purpose: Insert a Key and ElemType into the hashtable.
 			If the key exists, add the ElemType to the ValueType
 			within the LinkNode containing the Key. Accounts for 
 			collisions with linked list*/
template<typename ElemType>
void WordHash<ElemType>::insert(KeyType key, ElemType value_elem)
{
        expand();
        size_t index = hashFunction(key) % capacity;
        LinkNode *temp = table[index];
  		if (findKey(table[index], key, temp)) {
        	temp->value.insert(value_elem);
       	} else {
        	LinkNode *insert = new LinkNode;
        	insert->key = key;
        	insert->value.insert(value_elem);
        	insert->next = NULL;
        	if (table[index] == NULL)
        		table[index] = insert;
        	else {
        		temp->next = insert;
        	}
        	numElem++;
    	}	
}

/* findKey
 * parameters: LinkNode*, KeyType, LinkNode*&
 * return: bool
 * purpose: If the key is found, it will fill the LinkNode pointer
 			reference with the contents of the node of the node with the
 			key. It will then return true. Else it will return the last
 			node and return false */
template<typename ElemType>
bool WordHash<ElemType>::findKey(LinkNode* curr, KeyType key,
									LinkNode* &find)
{
	if (curr == NULL)
		return false;
	else if (curr->key == key) {
		find = curr;
		return true;
	} else {
		find = curr;
		return findKey(curr->next, key, find);
	}
}

/* getLast
 * parameters: LinkNode*
 * return: LinkNode*
 * purpose: Get the last Node of a linked list */
template<typename ElemType>
typename WordHash<ElemType>::LinkNode* WordHash<ElemType>::getLast(
													LinkNode* curr)
{
    if (curr->next != NULL)
        getLast(curr->next);
    return curr;
}

/* Expand
 * parameters: none
 * return: void
 * purpose: Checks if ratio of elements to capacity is too big
 			and increases capacity and rehashes each element */
template<typename ElemType>
void WordHash<ElemType>::expand()
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

/* insert
 * parameters: LinkNode*, LinkNode**
 * return: void
 * purpose: places given node in the new table at hashed index*/
template<typename ElemType>
void WordHash<ElemType>::insert(LinkNode* node, LinkNode** tempTable)
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

/* getLinesWith
 * parameters: const KeyType&, ValueType<ElemType>&
 * return: bool
 * purpose: if the key exists, the ValueType reference is filled
 			with the indexes corresponding to the key and return true
 			otherwise it returns false */
template<typename ElemType>
bool WordHash<ElemType>::getLinesWith(const KeyType& key,
										ValueType<ElemType>& list) 
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

/* print (for testing)
 * parameters: none
 * return: void
 * purpose: prints table */
template<typename ElemType>
void WordHash<ElemType>::print()
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
				for (ElemType elem : temp->value)
					std::cout << elem << ", ";
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
