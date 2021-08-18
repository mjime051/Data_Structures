#ifndef JUG_H
#define JUG_H

#include "pch.h"
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

struct Jugs {
	int jugA;
	int jugB;
	int cost;
	bool visited;
	Jugs* neighbors[6];
	Jugs* prev;
	Jugs(int, int);
};

class Jug {
public:
	Jug(int, int, int, int, int, int, int, int, int);
	~Jug();
	int solve(string &solution);
private:
	int capA;
	int capB;
	int wantedAmount;
	int costsArray[6];
	Jugs ***adjMatrix;
	void createGraph();
};

#endif // !JUG_H