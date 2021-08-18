#pragma once
#ifndef NODE_H
#define NODE_H

//#include "pch.h"
#include <string>

using namespace std;

class Node {
	friend class Tree;
private:
	string smallData;
	string largeData;
	Node* left;
	Node* middle;
	Node* right;
	Node* parent;

public:
	Node(string smallData, string largeData, Node* left = nullptr, Node* middle = nullptr, Node* right = nullptr);
};
#endif // !NODE_H
