//#include "pch.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
using namespace std;

Graph::Graph(ifstream& ifs) {
	int numVertex = 0;
	int numEdges = 0;
	//first two lines of file
	ifs >> numVertex;
	ifs >> numEdges;

	//next N lines--make a list and vector of these N nodes
	list<list<Vertex>> network;
	for (int i = 0; i < numVertex; i++) {
		Vertex newVertex = Vertex();
		ifs >> newVertex.label;
		vertices.push_back(newVertex);

		list<Vertex> newList;
		newList.push_back(newVertex);

		network.push_back(newList);
	}

	//next M lines--
	string firstLabel = "";
	string secondLabel = "";
	int dist = 0;
	for (int i = 0; i < numEdges; i++) {
		ifs >> firstLabel;
		ifs >> secondLabel;
		ifs >> dist;

		//create iterator
		list<list<Vertex>>::iterator it;
		//int firstIndex = 0;
		//int secondIndex = 0;
		for (it = network.begin(); it != network.end(); it++) {
			if (it->front().label != firstLabel) {
				continue;
			}
			else {
				Vertex newVertex = Vertex();
				newVertex.label = secondLabel;
				it->push_back(newVertex);
				//firstIndex = i;
			}
		}
		/*
		for(it = network.begin(); it != network.end(); it++){
			if(it->front().label != secondLabel){
				continue;
			}
			else{
				Vertex newVertex = Vertex();
				newVertex.label = firstLabel;
				it->push_back(newVertex);
				//secondIndex = i;
			}
		}
		*/

		//is this necessary considering you have the next for loop?
		/*
		pair<int,int> firstPair (firstIndex, 1);
		pair<int,int> secondPair (secondIndex, 1);
		vertices.at(firstIndex).neighbors.push_back(secondPair);
		vertices.at(secondIndex).neighbors.push_back(firstPair);
		*/
	}

	list<list<Vertex>>::iterator outerit;
	list<Vertex>::iterator innerit;
	int i = 0;
	for (outerit = network.begin(); outerit != network.end(); outerit++) {
		for (innerit = outerit->begin(); innerit != outerit->end(); innerit++) {
			if (innerit->label == outerit->front().label) {
				continue;
			}

			pair<int, int> newpair;
			for (unsigned j = 0; j < vertices.size(); j++) {
				if (vertices.at(j).label == innerit->label) {
					newpair.first = j;
					newpair.second = dist;
					outerit->front().neighbors.push_back(newpair);
					vertices.at(i).neighbors.push_back(newpair);
				}
			}

		}
		i++;
	}
}

void Graph::bfs() {
	vector<Vertex> discoveredSet;
	queue<Vertex*> frontierQueue;
	Vertex *currentVertex;

	Vertex *startVertex = &vertices.at(0);

	discoveredSet.push_back(*startVertex);
	frontierQueue.push(startVertex);


	//this is the starting point of your distance and previous
	int dist = 0;
	vertices.at(0).distance = dist;
	vertices.at(0).prev = 0;
	Vertex* previous = 0;
	while (!frontierQueue.empty()) {
		currentVertex = frontierQueue.front();
		//test
		cout << "Current Vertex: " << currentVertex->label << endl;

		frontierQueue.pop();

		previous = currentVertex->prev;

		while (previous != 0) {
			dist += 1;
			//cout << previous->prev->label << endl;
			previous = previous->prev;
		}
		currentVertex->distance = dist;
		dist = 0;

		//look through the neighbors
		list<pair<int, int>>::iterator it;
		for (it = currentVertex->neighbors.begin(); it != currentVertex->neighbors.end(); it++) {

			bool discovered = false;
			for (unsigned i = 0; i < discoveredSet.size(); i++) {
				if (vertices.at(it->first).label == discoveredSet.at(i).label) {
					discovered = true;
				}
			}
			if (!discovered) {
				frontierQueue.push(&vertices.at(it->first));
				discoveredSet.push_back(vertices.at(it->first));

				//test
				/*
				cout << "     Discovered so far: ";
				for(unsigned i = 0; i < discoveredSet.size(); i++){
					cout << discoveredSet.at(i).label << ", ";
				}
				cout << endl;
				*/

				vertices.at(it->first).prev = currentVertex;
				cout << "    Adjacent Vertex: " << vertices.at(it->first).label << endl;
				cout << "    Previous (current) Vertex: " << vertices.at(it->first).prev->label << endl;
				//not sure about this line
			}

		}
	}

}

void Graph::printPath(Vertex currVertex) {
	while (currVertex.prev != 0) {
		cout << currVertex.label << endl;
		currVertex = *currVertex.prev;
	}
}

void Graph::printGraph() {
	for (unsigned i = 0; i < vertices.size(); i++) {
		cout << "Vertex " << i << ": " << vertices.at(i).label << endl;
		list<pair<int, int>>::iterator it;
		for (it = vertices.at(i).neighbors.begin(); it != vertices.at(i).neighbors.end(); it++) {
			cout << "    Neighbor: " << vertices.at(it->first).label << ", " << vertices.at(it->first).distance << endl;
		}
	}
}

/*
visualizeTree(const string &outputFilename){
	ofstream outFS(outputFilename.c_str());
	if(!outFS.is_open()){
		cout<<"Error opening "<< outputFilename<<endl;
		return;
	}
	outFS<<"digraph G {"<<endl;
	visualizeTree(outFS,root);
	outFS<<"}";
	outFS.close();
	string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
	string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
	system(command.c_str());
}
*/