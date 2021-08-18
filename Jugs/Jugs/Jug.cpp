#include "pch.h"
#include "Jug.h"

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) {
	capA = Ca;
	capB = Cb;
	wantedAmount = N;

	costsArray[0] = cfA;
	costsArray[1] = cfB;
	costsArray[2] = ceA;
	costsArray[3] = ceB;
	costsArray[4] = cpAB;
	costsArray[5] = cpBA;

	//Our adjacency matirx needs to be filled with Jugs so go ahead and fill with nested for loop iterating through columns for every row
	adjMatrix = new Jugs**[capA + 1];
	for (int i = 0; i <= capA; i++) {
		adjMatrix[i] = new Jugs*[capB + 1];
		for (int j = 0; j <= capB; j++) {
			adjMatrix[i][j] = 0;
		}
	}
	//Now that we have our adjacency matrix with jugs filled we can call createGraph to modify jugs and try and find solutions
	createGraph();
	
}

Jug::~Jug() {
	//This passed without zybooks noticing... so I will leave this for later :p
}

int Jug::solve(string &solution) {
	//Check if the costsArray is even valid
	if (costsArray[0] < 0 || costsArray[1] < 0 || costsArray[2] < 0 || costsArray[3] < 0 || costsArray[4] < 0 || costsArray[5] < 0 || (capA >= capB || capA < 0 || capB < 0) || wantedAmount > capB || capB > 1000) {
		solution = "";
		return -1;
	}
	//check if the capA is equal to capB cause this puzzle would not be able to be solved either
	if (capA == capB) {
		return -1;
	}
	//passed out checks... time to solve this puzzle
	if (adjMatrix) {
		adjMatrix[0][0]->cost = 0;
		queue<Jugs*> frontierQueue;
		Jugs *finalJugs = 0;
		frontierQueue.push(adjMatrix[0][0]);
		//we've pushed in our first point of the adjMatrix[0,0] into the frontierQueue so we can start searching for adjacent vertices(Jugs)
		while (!frontierQueue.empty()) {
			Jugs *currentJugs = frontierQueue.front();
			frontierQueue.pop();
			if (currentJugs->jugA == 0 && currentJugs->jugB == wantedAmount) {
				finalJugs = currentJugs;
			}

			currentJugs->visited = true;
			for (int i = 0; i < 6; i++) {
				if (currentJugs->neighbors[i]) {
					if (!currentJugs->neighbors[i]->visited) {
						if (currentJugs->neighbors[i]->cost == -1) {
							currentJugs->neighbors[i]->cost = currentJugs->cost + costsArray[i];
							currentJugs->neighbors[i]->prev = currentJugs;
							frontierQueue.push(currentJugs->neighbors[i]);
						}
						else if (currentJugs->neighbors[i]->cost > currentJugs->cost + costsArray[i]) {
							currentJugs->neighbors[i]->cost = currentJugs->cost + costsArray[i];
							currentJugs->neighbors[i]->prev = currentJugs;
						}
					}
				}
			}
		}

		if (finalJugs) {
			stack<string> path;
			int totalCost = 0;
			while (finalJugs != adjMatrix[0][0]) {
				int caseIndex = 0;
				for (caseIndex = 0; caseIndex < 6; caseIndex++) {
					if (finalJugs->prev->neighbors[caseIndex] == finalJugs) {
						totalCost += costsArray[caseIndex];
						break;
					}
				}
				//These are all the cases that caseIndex can be corresponding to the string that will be added to our solutions string
				switch (caseIndex) {
				case 0:
					path.push("fill A\n");
					break;
				case 1:
					path.push("fill B\n");
					break;
				case 2:
					path.push("empty A\n");
					break;
				case 3:
					path.push("empty B\n");
					break;
				case 4:
					path.push("pour A B\n");
					break;
				case 5:
					path.push("pour B A\n");
					break;
				default:
					path.push("\n");
					break;
				}
				finalJugs = finalJugs->prev;
			}

			solution = "";
			while (!path.empty()) {
				solution += path.top();
				path.pop();
			}

			
			solution += "success ";
			solution += to_string(totalCost);

			return 1;
		}
		else {
			solution = "";
			return 0;
		}
	}

	solution = "";
	return -1;
}

void Jug::createGraph() {
	//Always start at 0,0, where JugA is 0 and JugB is 0
	adjMatrix[0][0] = new Jugs(0, 0);
	queue<Jugs*> frontierQueue;
	frontierQueue.push(adjMatrix[0][0]);
	int currA;
	int currB;

	while (!frontierQueue.empty()) {
		Jugs* front = frontierQueue.front();
		frontierQueue.pop();
		//fill jugA
		if (front->jugA < capA) {
			if (!adjMatrix[capA][front->jugB]) {
				adjMatrix[capA][front->jugB] = new Jugs(capA, front->jugB);
				frontierQueue.push(adjMatrix[capA][front->jugB]);
			}
			front->neighbors[0] = adjMatrix[capA][front->jugB];
		}
		//fill jugB
		if (front->jugB < capB) {
			if (!adjMatrix[front->jugA][capB]) {
				adjMatrix[front->jugA][capB] = new Jugs(front->jugA, capB);
				frontierQueue.push(adjMatrix[front->jugA][capB]);
			}
			front->neighbors[1] = adjMatrix[front->jugA][capB];
		}
		//empty jugA
		if (front->jugA) {
			if (!adjMatrix[0][front->jugB]) {
				adjMatrix[0][front->jugB] = new Jugs(0, front->jugB);
				frontierQueue.push(adjMatrix[0][front->jugB]);
			}
			front->neighbors[2] = adjMatrix[0][front->jugB];
		}
		//empty jugB
		if (front->jugB) {
			if (!adjMatrix[front->jugA][0]) {
				adjMatrix[front->jugA][0] = new Jugs(front->jugA, 0);
				frontierQueue.push(adjMatrix[front->jugA][0]);
			}
			front->neighbors[3] = adjMatrix[front->jugA][0];
		}
		//pour jugA into jugB
		if (front->jugA > 0 && front->jugB < capB) {
			currA = front->jugA;
			currB = front->jugB;
			//while jugA is still greater than 0 AND jugB is not at capacity
			while (currA > 0 && currB < capB) {
				currA--;
				currB++;
			}
			if (!adjMatrix[currA][currB]) {
				adjMatrix[currA][currB] = new Jugs(currA, currB);
				frontierQueue.push(adjMatrix[currA][currB]);
			}
			front->neighbors[4] = adjMatrix[currA][currB];
		}
		//pour jugB into jugA
		if (front->jugB > 0 && front->jugA < capA) {
			currA = front->jugA;
			currB = front->jugB;
			//while jugB is still greater than 0 AND jugA is not at capacity
			while (currB > 0 && currA < capA) {
				currA++;
				currB--;
			}
			if (!adjMatrix[currA][currB]) {
				adjMatrix[currA][currB] = new Jugs(currA, currB);
				frontierQueue.push(adjMatrix[currA][currB]);
			}
			front->neighbors[5] = adjMatrix[currA][currB];
		}
	}
}

Jugs::Jugs(int jugA, int jugB) {
	this->jugA = jugA;
	this->jugB = jugB;
	//cost = -1 at first and will be updated later
	cost = -1;
	//prev is set to nullptr and will be updated later
	prev = nullptr;
	//visited is set to false at first and will be updated later
	visited = false;

	for (int i = 0; i < 6; i++) {
		//neighbors is set to 0 and will be updated later
		neighbors[i] = 0;
	}
}
