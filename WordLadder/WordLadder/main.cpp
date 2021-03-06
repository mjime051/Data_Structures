#include "pch.h"
#include "WordLadder.h"

int main() {
	string inputFile, startWord, endWord, outputFile;
		cout << "Please enter the input file to create the dictionary: ";
		cin >> inputFile;

		cout << "Please enter a word: ";
		cin >> startWord;

		cout << "Please enter another word of the same length: ";
		cin >> endWord;

		cout << "Please enter the output file in which you want your wordLadder to go into: ";
		cin >> outputFile;

	WordLadder *wordLadderTest = new WordLadder(inputFile);
	wordLadderTest->outputLadder(startWord, endWord, outputFile);

	return 0;
}