#include "pch.h"
#include "WordLadder.h"

WordLadder::WordLadder(const string &inputFile) {
	string currentWord;
	ifstream dictionary(inputFile);
	
		if (!dictionary.is_open()) {
			cout << "Invalid File!" << endl;
			return;
		}
		while (!dictionary.eof()) {
			if (!dictionary.fail()) {
				dictionary >> currentWord;
				if (currentWord.size() != 5) {
					cout << "Invalid File!" << endl;
					return;
				}
				dict.push_back(currentWord);
			}
		}
	dictionary.close();
}

void WordLadder :: outputLadder(const string &start, const string &end, const string &outputFile) {

	queue<stack<string>> queueOfStacks;

	stack<string> potentialWordLadder;
	stack<string> copyOfStack;
	stack<string> actualWordLadder;
	list<string> ::iterator currWordInDict;
	string currentWord, wordToBeRemoved;
	int numOfOneOffLetters = 0;
	potentialWordLadder.push(start);
	queueOfStacks.push(potentialWordLadder);
	ofstream outFile;
	outFile.open(outputFile);

	while (!queueOfStacks.empty()) {
		currentWord = (queueOfStacks.front()).top();

		if (currentWord == end) {
			break;
		}

			for (currWordInDict = dict.begin(); currWordInDict != dict.end(); currWordInDict++) {
				for (unsigned currCharacterIndex = 0; currCharacterIndex < currentWord.size(); currCharacterIndex++) {
					if (currentWord.at(currCharacterIndex) != (*currWordInDict).at(currCharacterIndex)) {
						numOfOneOffLetters++;
					}
				}

				if (numOfOneOffLetters == 1) {
					copyOfStack = queueOfStacks.front();
					copyOfStack.push(*currWordInDict);
					
					queueOfStacks.push(copyOfStack);
					//wordToBeRemoved = *currWordInDict;
					//cout << "the neighbor being pushed in is " << *currWordInDict << endl;
					//currWordInDict++;
					
					dict.erase(currWordInDict--);
				}

				numOfOneOffLetters = 0;
			}
		

		queueOfStacks.pop();
	}

	if (queueOfStacks.empty()) {
		outFile << "No Word Ladder Found.";
	}
	else {
		while (!(queueOfStacks.front()).empty()) {
			actualWordLadder.push(queueOfStacks.front().top());
			queueOfStacks.front().pop();
		}

		while (!actualWordLadder.empty()) {
			if (actualWordLadder.top() == end) {
				outFile << actualWordLadder.top();
				actualWordLadder.pop();
			}
			else {
				outFile << actualWordLadder.top() << " ";
				actualWordLadder.pop();
			}
		}
		
	}
	outFile.close();
}
