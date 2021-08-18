#ifndef __BSTREE_H__
#define __BSTREE_H__

#include "pch.h"
#include "Node.h"

using namespace std;

class BSTree {

private:
	Node *root;

private:
	bool search(Node* curr, const string &key) const;
	void inOrder(Node* curr) const;
	void postOrder(Node* curr) const;
	void preOrder(Node* curr) const;
	string largest(Node* curr) const;
	string smallest(Node* curr) const;
	int height(Node* curr, const string &) const;
	void remove(Node* curr, Node*par, const string &);

public:
	BSTree();
	void insert(const string &);
	bool search(const string &) const;
	void inOrder() const;
	void postOrder() const;
	void preOrder() const;
	string largest() const;
	string smallest() const;
	int height(const string &) const;
	void remove(const string &);
};

#endif