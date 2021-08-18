#include "pch.h"
#include "BSTree.h"

BSTree::BSTree() {
	root = nullptr;
}
bool BSTree::search(const string &key) const{
	bool found;
	found = search(root, key);
	return found;
}

bool BSTree::search(Node* curr, const string &key) const {
	Node* current = curr;
	if (current == nullptr) {
		return false;
	}
	else if (key == current->data) {
		return true;
	}
	else if (key < current->data) {
		return search(current->leftChild, key);
	}
	else {
		return search(current->rightChild, key);
	}
}

void BSTree::inOrder() const {
	inOrder(root);
}

void BSTree::inOrder(Node* curr) const {
	Node* current = curr;
	if (current != nullptr) {
		inOrder(current->leftChild);
		cout << current->data << "(" << current->count << "), ";
		inOrder(current->rightChild);
	}
}

void BSTree::preOrder() const {
	preOrder(root);
}

void BSTree::preOrder(Node* curr) const {
	Node* current = curr;
	if (current != nullptr) {
		cout << current->data << "(" << current->count << "), ";
		preOrder(current->leftChild);
		preOrder(current->rightChild);
	}
}

void BSTree::postOrder() const {
	postOrder(root);
}

void BSTree::postOrder(Node* curr) const {
	Node* current = curr;
	if (current != nullptr) {
		postOrder(current->leftChild);
		postOrder(current->rightChild);
		cout << current->data << "(" << current->count << "), ";
	}
}

void BSTree::insert(const string &key) {
	Node* current = root;
	
	Node* newNode = new Node(key);
	while (current != nullptr) {
		if (current->data == key) {
			current->count++;
			return;
		}
		else if (key < current->data) {
			current = current->leftChild;
		}
		else {
			current = current->rightChild;
		}
	}
	if (root == nullptr) {
		root = newNode;
		return;
	}
	current = root;

	while (current != nullptr) {
		if (newNode->data < current->data) {
			if (current->leftChild == nullptr) {
				current->leftChild = newNode;
				current = nullptr;
			}
			else {
				current = current->leftChild;
			}
		}
		else {
			if (current->rightChild == nullptr) {
				current->rightChild = newNode;
				current = nullptr;
			}
			else {
				current = current->rightChild;
			}
		}
		/*else if (newNode->data == current->data) {
			current->count++;
		}
		*/
	}
}

string BSTree::largest() const{
	Node* current = root;
	return largest(current);
}

string BSTree::largest(Node* curr) const {
	Node* current = curr;
	string largeString;
	while (current != nullptr) {
		largeString = current->data;
		current = current->rightChild;
	}
	return largeString;
}
string BSTree::smallest() const {
	Node* current = root;
	return smallest(current);
}

string BSTree::smallest(Node* curr) const {
	Node* current = curr;
	string smallString;
	while (current != nullptr) {
		smallString = current->data;
		current = current->leftChild;
	}
	return smallString;
}

int BSTree::height(const string &key) const {
	Node* current = root;
	bool found = false;

	while (current != nullptr && !found) {
		if (key == current->data) {
			found = true;
		}
		else if (key < current->data) {
			current = current->leftChild;
		}
		else {
			current = current->rightChild;
		}
	}

	return height(current, key);
}

int BSTree::height(Node* curr, const string &key) const {
	Node* current = curr;
	if (current == nullptr) {
		return -1;
	}
	else {
		int leftCount = height(current->leftChild, key);
		int rightCount = height(current->rightChild, key);
		if (leftCount > rightCount) {
			return (leftCount + 1);
		}
		else {
			return (rightCount + 1);
		}
	}
}

void BSTree::remove(const string &key) {
	if (root == nullptr || key == "") {
		return;
	}
	remove(root, nullptr, key);
}

void BSTree::remove(Node* curr, Node* par, const string &key) {
	Node* parent = par;
	Node* current = curr;
	int tempCount;
	string tempData;

	if (root->data == key && root->leftChild == nullptr && root->rightChild == nullptr) {
		if (root->count > 1) {
			root->count--;
			return;
		}
		else {
			current = root;
			root = nullptr;
			delete current;
			return;
		}
	}

	while (current != nullptr) {
		if (key == current->data) {
			if (current->count > 1) {
				current->count--;
				return;
			}

			if (current->leftChild == nullptr && current->rightChild == nullptr) {
				if (parent->leftChild == current) {
					parent->leftChild = nullptr;
					delete current;
					current = nullptr;
				}
				else {
					parent->rightChild = nullptr;
					delete current;
					current = nullptr;
				}
			}

			else if (current->leftChild == nullptr && current->rightChild != nullptr) {
				curr = current;
				par = parent;
				parent = current;
				current = current->rightChild;

				while (current->leftChild != nullptr) {
					parent = current;
					current = current->leftChild;
				}

				tempData = current->data;
				tempCount = current->count;
				current->data = curr->data;
				current->count = curr->count;
				curr->data = tempData;
				curr->count = tempCount;
				remove(current, parent, current->data);
				return;
			}

			else {
				curr = current;
				par = parent;
				parent = current;
				current = current->leftChild;

				while (current->rightChild != nullptr) {
					parent = current;
					current = current->rightChild;
				}

				tempData = current->data;
				tempCount = current->count;
				current->data = curr->data;
				current->count = curr->count;
				curr->data = tempData;
				curr->count = tempCount;
				remove(current, parent, current->data);
				return;
			}

		}

		else if (key < current->data) {
			parent = current;
			current = current->leftChild;
		}
		else {
			parent = current;
			current = current->rightChild;
		}
	}
	return;
}