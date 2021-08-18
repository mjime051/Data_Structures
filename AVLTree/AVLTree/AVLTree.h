#ifndef AVLTREE_H
#define AVLTREE_H

#include "pch.h"
#include "Node.h"
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>

using namespace std;

class AVLTree {
public:
	AVLTree();
	void insert(const string &key);
	int balanceFactor(Node* curr);
	void printBalanceFactors();
	void visualizeTree(const string &key);
	
private:
	void updateHeight(Node* curr);
	Node* getParent(const string &key);
	Node* findUnbalancedNode(Node* curr);
	void rotate(Node* curr);
	void rotateLeft(Node* curr);
	void rotateRight(Node* curr);
	void printBalanceFactors(Node* curr);
	void visualizeTree(ofstream &outFile, Node *curr);
	Node* root;
};

#endif // !AVLTREE_H
