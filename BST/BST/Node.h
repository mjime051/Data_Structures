#ifndef NODE_H
#define NODE_H
#include "pch.h"
#include<string>
#include<iostream>


class Node {
friend class BSTree;
private:
	std::string data;
	int count;
	Node* leftChild;
	Node* rightChild;

public:
	Node(std::string value);
};
#endif // !NODE_H
