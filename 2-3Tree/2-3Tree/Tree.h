#pragma once
#ifndef TREE_H
#define TREE_H

//#include "pch.h"
#include "Node.h"
#include <iostream>

using namespace std;

class Tree {
private:
	Node* root;
	void preOrder(Node* curr)const;
	void inOrder(Node* curr) const;
	void postOrder(Node* curr) const;
	bool search(const string &key, Node* curr) const;
	void split(Node* par, const string &middlest, Node* newSmall, Node* newLarge);
	void fix(Node* curr);

public:
	Tree();
	void preOrder() const;
	void inOrder() const;
	void postOrder() const;
	void insert(const string &data);
	void remove(const string &data);
	bool search(const string &key) const;
};

#endif // !TREE_H
