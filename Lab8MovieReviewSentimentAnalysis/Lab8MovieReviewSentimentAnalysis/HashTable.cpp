#include "pch.h"
#include "HashTable.h"
#include "WordEntry.h"
#include <math.h>

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable(int s) {
	this->size = s;
	this->hashTable = new list<WordEntry>[size];
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
	int hash = 0;
	unsigned index;
	for(index = 0; index < s.length(); index++){
		hash *= 31;
		hash += s[index];
	}
	hash = abs(hash);
	return (hash % size);
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
	int hashVal = computeHash(s);
	list<WordEntry> ::iterator currWordEntry;
	
	for (currWordEntry = hashTable[hashVal].begin(); currWordEntry != hashTable[hashVal].end(); currWordEntry++) {
		if (s == currWordEntry->getWord()) {
			currWordEntry->addNewAppearance(score);
			return;
		}
	}
	WordEntry newEntry = WordEntry(s, score);
	hashTable[hashVal].push_back(newEntry);
}

/* getAverage
*  input: string word
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
	int hashVal = computeHash(s);
	list<WordEntry> ::iterator currWordEntry;

	for (currWordEntry = hashTable[hashVal].begin(); currWordEntry != hashTable[hashVal].end(); currWordEntry++) {
		if (s == currWordEntry->getWord()) {
			double avg = currWordEntry->getAverage();
			return avg;
		}
	}
	return 2.0;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
	int hashVal = computeHash(s);
	list<WordEntry> ::iterator currWordEntry;

	for (currWordEntry = hashTable[hashVal].begin(); currWordEntry != hashTable[hashVal].end(); currWordEntry++) {
		if (s == currWordEntry->getWord()) {
			return true;
		}
	}
	return false;
}
