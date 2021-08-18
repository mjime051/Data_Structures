#include "pch.h"
#include "AVLTree.h"

AVLTree::AVLTree() {
	root = nullptr;
}

void AVLTree::printBalanceFactors() {
	printBalanceFactors(root);
}

Node* AVLTree::getParent(const string &key) {
	Node* current = root;
	if (key == root->data) {
		return nullptr;
	}
	while (current != nullptr) {
		if (current->left != nullptr && key == current->left->data) {
			return current;
		}
		else if (current->right != nullptr && key == current->right->data) {
			return current;
		}
		else if (key < current->data) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return nullptr;
}

void AVLTree::printBalanceFactors(Node* curr) {
	Node* current = curr;
	if (current != nullptr) {
		printBalanceFactors(current->left);
		//cout << "I havent tried to print yet" << endl;
		cout << current->data << "(" << balanceFactor(current) << "), ";
		//cout << "Ive tried to print" << endl;
		printBalanceFactors(current->right);
	}
}

Node* AVLTree::findUnbalancedNode(Node* curr) {
	if (curr == nullptr) {
		return nullptr;
	}
	if ((balanceFactor(curr) > 1) || (balanceFactor(curr) < -1)) {
		return curr;
	}
	else {
		return findUnbalancedNode(getParent(curr->data));
	}
}

void AVLTree::insert(const std::string &data) {
	if (data == "" || data == " ") {
		std::cout << "Empty string. Try again.\n";
		return;
	}
	if (this->root == nullptr) {
		this->root = new Node(data);
		return;
	}

	Node* current = this->root;
	bool heightChange = false;

	while (current != nullptr) {
		if (current->data == data) {
			return;
		}
		if (data < current->data) {
			if (current->left == nullptr && current->right == nullptr) {
				current->left = new Node(data);
				heightChange = true;
				current = current->left;
				break;
			}
			else if (current->left == nullptr) {
				current->left = new Node(data);
				current = current->left;
				break;
			}
			else {
				current = current->left;
			}
		}
		else {
			if (current->left == nullptr && current->right == nullptr) {
				current->right = new Node(data);
				heightChange = true;
				current = current->right;
				break;
			}
			else if (current->right == nullptr) {
				current->right = new Node(data);
				current = current->right;
				break;
			}
			else {
				current = current->right;
			}
		}
	}

	if (heightChange == false) {
		return;
	}
	else {
		Node* parent = getParent(current->data);
		while (parent != nullptr) {
			parent->height++;
			parent = getParent(parent->data);
		}

		current = findUnbalancedNode(current);
		if (current != nullptr) {
			rotate(current);
		}
	}
}

void AVLTree::updateHeight(Node* node) {
	int leftHeight = -1;
	int rightHeight = -1;

	if (node->left != nullptr) {
		leftHeight = node->left->height;
	}

	if (node->right != nullptr) {
		rightHeight = node->right->height;
	}

	if (leftHeight > rightHeight) {
		node->height = leftHeight + 1;
	}
	else {
		node->height = rightHeight + 1;
	}
}


void AVLTree::rotate(Node* current) {
	if (balanceFactor(current) == 2) {
		if (balanceFactor(current->left) == -1) {
			rotateLeft(current->left);
		}
		rotateRight(current);
	}
	else if (balanceFactor(current) == -2) {
		if (balanceFactor(current->right) == 1) {
			rotateRight(current->right);
		}
		rotateLeft(current);
	}
}


void AVLTree::rotateLeft(Node* current) {
	Node* parent = getParent(current->data);
	Node* rightChild = current->right;

	if (parent != nullptr) {
		if (parent->left == current) {
			parent->left = rightChild;
		}
		else {
			parent->right = rightChild;
		}
		current->right = rightChild->left;
		rightChild->left = current;

		updateHeight(current);
		updateHeight(rightChild);
	}
	else {
		root = rightChild;
		current->right = rightChild->left;
		rightChild->left = current;

		updateHeight(rightChild->left);
		updateHeight(root);
	}
}


void AVLTree::rotateRight(Node* current) {
	Node* parent = getParent(current->data);
	Node* leftChild = current->left;

	if (parent != nullptr) {
		if (parent->left == current) {
			parent->left = leftChild;
		}
		else {
			parent->right = leftChild;
		}
		current->left = leftChild->right;
		leftChild->right = current;

		updateHeight(current);
		updateHeight(leftChild);
	}
	else {
		root = leftChild;
		current->left = leftChild->right;
		leftChild->right = current;

		updateHeight(leftChild->right);
		updateHeight(root);
	}
}

int AVLTree::balanceFactor(Node* node) {
	int leftHeight, rightHeight;
	if (node->left != nullptr) {
		leftHeight = (node->left)->height;
	}
	else {
		leftHeight = -1;
	}

	if (node->right != nullptr) {
		rightHeight = (node->right)->height;
	}
	else {
		rightHeight = -1;
	}

	return leftHeight - rightHeight;
}



void AVLTree::visualizeTree(const string &outputFilename) {
	ofstream outFS(outputFilename.c_str());
	if (!outFS.is_open()) {
		cout << "Error" << endl;
		return;
	}
	outFS << "digraph G {" << endl;
	visualizeTree(outFS, root);
	outFS << "}";
	outFS.close();
	string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
	string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
	system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n) {
	if (n) {
		if (n->left) {
			visualizeTree(outFS, n->left);
			outFS << n->data << " -> " << n->left->data << ";" << endl;
		}

		if (n->right) {
			visualizeTree(outFS, n->right);
			outFS << n->data << " -> " << n->right->data << ";" << endl;
		}
	}
}