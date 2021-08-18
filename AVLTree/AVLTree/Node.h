#pragma once
#include "pch.h"
#ifndef NODE_H
#define NODE_H
#include<string>
#include<iostream>

class Node {
	friend class AVLTree;
private:
	std::string data;
	//int count;
	int height;
	Node* left;
	Node* right;

public:
	Node(std::string value);
};
#endif // !NODE_H
