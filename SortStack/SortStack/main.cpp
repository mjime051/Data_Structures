// SortStack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int main()
{
	stack<int> stackOfInts;
	stackOfInts.push(0);
	cout << "Num inserted: 0" << endl;
	stackOfInts.push(5);
	cout << "Num inserted: 5" << endl;
	stackOfInts.push(7);
	cout << "Num inserted: 7" << endl;
	stackOfInts.push(2);
	cout << "Num inserted: 2" << endl;
	stackOfInts.push(8);
	cout << "Num inserted: 8" << endl;
	stackOfInts.push(1);
	cout << "Num inserted: 1" << endl;
	stackOfInts.push(9);
	cout << "Num inserted: 9" << endl;
	stackOfInts.push(6);
	cout << "Num inserted: 6" << endl;
	stackOfInts.push(3);
	cout << "Num inserted: 3" << endl;
	
	queue<int> sortingQ;
	int newFrontValue;
	int temp;

	sortingQ.push(stackOfInts.top());
	stackOfInts.pop();

	while (!stackOfInts.empty()) {
		if (stackOfInts.top() < sortingQ.front()) {
			newFrontValue = stackOfInts.top();
			sortingQ.push(stackOfInts.top());
		}

		else {
			newFrontValue = sortingQ.front();
			temp = sortingQ.front();
			sortingQ.pop();
			sortingQ.push(temp);
			while (stackOfInts.top() > sortingQ.front() && sortingQ.front() != newFrontValue) {
				temp = sortingQ.front();
				sortingQ.pop();
				sortingQ.push(temp);
			}
			sortingQ.push(stackOfInts.top());

		}
		while (sortingQ.front() != newFrontValue) {
			temp = sortingQ.front();
			sortingQ.pop();
			sortingQ.push(temp);
		}
		stackOfInts.pop();
	}
	
	while (!sortingQ.empty()) {
		temp = sortingQ.front();
		sortingQ.pop();
		stackOfInts.push(temp);
	}

	while (!stackOfInts.empty()) {
		cout << stackOfInts.top() << endl;
		stackOfInts.pop();
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
