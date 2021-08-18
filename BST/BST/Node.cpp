#include "pch.h"
#include "Node.h"

Node::Node(std::string value) {
	this->leftChild = nullptr;
	this->rightChild = nullptr;
	this->count = 1;
	this->data = value;
}