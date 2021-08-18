#include "pch.h"
#include "Node.h"

Node::Node(std::string value) {
	this->left = nullptr;
	this->right = nullptr;
	//this->count = 1;
	this->height = 0;
	this->data = value;
}