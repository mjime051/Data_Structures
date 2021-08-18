//#include "pch.h"
#include "Node.h"

Node::Node(string small, string large, Node* leftChild, Node* middleChild, Node* rightChild) {
	this->smallData = small;
	this->largeData = large;
	this->left = leftChild;
	this->middle = middleChild;
	this->right = rightChild;
}