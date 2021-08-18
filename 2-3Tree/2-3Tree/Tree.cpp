//#include "pch.h"
#include "Tree.h"

using namespace std;

Tree::Tree() {
	root = nullptr;
}

void Tree::inOrder() const {
	inOrder(root);
}

void Tree::inOrder(Node* curr) const {
	Node* current = curr;
	if (current != nullptr) {
		inOrder(current->left);
		if (current->smallData != "") {
			cout << current->smallData << ", ";
		}
		inOrder(current->middle);
		if (current->largeData != "") {
			cout << current->largeData << ", ";
		}
		inOrder(current->right);
	}
}

void Tree::preOrder() const {
	preOrder(root);
}

void Tree::preOrder(Node* curr) const {
	Node* current = curr;
	if (current != nullptr) {
		if (current->smallData != "") {
			cout << current->smallData << ", ";
		}
		preOrder(current->left);
		if (current->largeData != "") {
			cout << current->largeData << ", ";
		}
		preOrder(current->middle);
		preOrder(current->right);
	}
}

void Tree::postOrder() const {
	postOrder(root);
}

void Tree::postOrder(Node* curr) const {
	Node* current = curr;
	if (current != nullptr) {
		if (current->smallData != "" && current->largeData != "") {
			postOrder(current->left);
			postOrder(current->middle);
			if (current->smallData != "") {
				cout << current->smallData << ", ";
			}
			postOrder(current->right);
			if (current->largeData != "") {
				cout << current->largeData << ", ";
			}
		}
		else {
			postOrder(current->left);
			//postOrder(current->middle);
			postOrder(current->right);
			if (curr->smallData != "") {
				cout << current->smallData << ", ";
			}
		}
	}
}

bool Tree::search(const string &key) const {
	bool found;
	found = search(key, root);
	return found;
}

bool Tree::search(const string &key, Node* curr) const {
	Node* current = curr;
	if (current != nullptr) {
		if (current->smallData == key || current->largeData == key) {
			return true;
		}
		else {
			if (key < current->smallData) {
				return search(key, current->left);
			}
			else if (key < current->largeData) {
				return search(key, current->middle);
			}
			else {
				return search(key, current->right);
			}
		}
	}
	return false;
}

void Tree::insert(const string &key) {
	if (root == nullptr) {
		//cout << "I am making a root node" << endl;
		Node* newNode = new Node(key, "");
		root = newNode;
		return;
	}

	Node* current = root;
	//cout << "Trying to enter another value into my tree" << endl;
	while (current != nullptr) {
		//cout << "I entered my loop to enter another value" << endl;
		//We are at a leaf node
		if (current->left == nullptr && current->right == nullptr) {
			//We are at a three node
			if (current->largeData != "") {
				//Split here
				split(current, key, nullptr, nullptr);
				current = nullptr;
			}
			//We are at a two node
			else {
				if (key < current->smallData) {
					current->largeData = current->smallData;
					current->smallData = key;
					current = nullptr;
				}
				else {
					current->largeData = key;
					current = nullptr;
				}
			}
		}
		//We are not at a leaf node
		else {
			//We are at a three node
			if (current->largeData != "") {
				if (key < current->smallData) {
					current = current->left;
				}
				else if (key > current->largeData) {
					current = current->right;
				}
				else {
					current = current->middle;
				}
			}
			//We are at a two node
			else {
				if (key < current->smallData) {
					current = current->left;
				}
				else {
					current = current->right;
				}
			}
		}
	}
}

void Tree::split(Node* curr, const string &key, Node* passedLeft, Node* passedRight) {
	
	Node* newRootNode;
	Node* newParent;
	string smallest, middlest, largest;
	//Need to determine what the smallest, middle, largest is
	if (key < curr->smallData) {
		//key was smaller than smallData so it will become smallest
		smallest = key;
		middlest = curr->smallData;
		largest = curr->largeData;
	}
	else if (key > curr->largeData) {
		//key is greater than largeData so it will become largest
		smallest = curr->smallData;
		middlest = curr->largeData;
		largest = key;
	}
	else {
		//key is greater than smallData and less than largeData so it will become middle
		smallest = curr->smallData;
		middlest = key;
		largest = curr->largeData;
	}
	//if you are at the root then you must create a new node for parent;
	if (curr == root) {
		newRootNode = new Node(middlest, "");
		newParent = newRootNode;
		//cout << "my new parents data is " << newParent->smallData << endl;
		root = newParent;
	}
	//otherwise you can just access the curr's parent
	else {
		newParent = curr->parent;
	}
	//Must create a newNode so we can store the smallData of curr
	Node* newNodeSmall = new Node(smallest, "");
	//cout << "my new nodes data is " << newNodeOne->smallData << endl;
	newNodeSmall->parent = newParent;
	//cout << "my new nodes parent is " << newNodeOne->parent->smallData << endl;
	Node* newNodeLarge = new Node(largest, "");
	newNodeLarge->parent = newParent;
	
	//I am currently splitting at an internal node and need to reassign the children
	
	if (curr->left != nullptr) {
		//cout << "I am an internal node" << endl;
		if (passedLeft->smallData < curr->smallData) {
			//cout << "I split from my left child before this" << endl;
			newNodeSmall->left = passedLeft;
			passedLeft->parent = newNodeSmall;
			newNodeSmall->right = passedRight;
			passedRight->parent = newNodeLarge;
			newNodeLarge->left = curr->middle;
			curr->middle->parent = newNodeLarge;
			newNodeLarge->right = curr->right;
			curr->right->parent = newNodeLarge;
		}
		else if (passedLeft->smallData < middlest) {
			//cout << "I split from my middle child before this" << endl;
			newNodeSmall->left = curr->left;
			curr->left->parent = newNodeSmall;
			newNodeSmall->right = passedLeft;
			passedLeft->parent = newNodeSmall;
			newNodeLarge->left = passedRight;
			passedRight->parent = newNodeLarge;
			newNodeLarge->right = curr->right;
			curr->right->parent = newNodeLarge;
		}
		else {
			//cout << "I split from my right child before this" << endl;
			newNodeSmall->left = curr->left;
			curr->left->parent = newNodeSmall;
			newNodeSmall->right = curr->middle;
			curr->middle->parent = newNodeSmall;
			newNodeLarge->left = passedLeft;
			passedLeft->parent = newNodeLarge;
			newNodeLarge->right = passedRight;
			passedRight->parent = newNodeLarge;
		}
	}

	//delete curr;
	//curr = nullptr;

	//if our parent is a three node we cannot just insert our pushed up data, so we have to call split on our parent with our pushed up data
	if (newParent->largeData != "") {
		//cout << "Do i need to split more?" << endl;
		split(newParent, middlest, newNodeSmall, newNodeLarge);
	}
	//if our parent is a two node, we just have to check where to put in our pushed up middle
	else {
		//cout << "Do i go in here?" << endl;
		if (middlest < newParent->smallData) {
			newParent->largeData = newParent->smallData;
			newParent->smallData = middlest;
		}
		else if(middlest != newParent->smallData){
			newParent->largeData = middlest;
		}

		if (newParent->left == nullptr && newParent->right == nullptr) {
			newParent->left = newNodeSmall;
			newParent->right = newNodeLarge;
		}
		else if (newParent->right->smallData == curr->smallData) {
			newParent->middle = newNodeSmall;
			newParent->right = newNodeLarge;
		}
		else {
			newParent->left = newNodeSmall;
			newParent->middle = newNodeLarge;
		}
	}

}

void Tree::remove(const string &key) {
	Node* current = root;
	Node* leafNode;
	if (root == nullptr) {
		//cout << "Nothing was in the tree" << endl;
		return;
	}
	//cout << "Gotta find where to remove first" << endl;
	while (current != nullptr) {
		if (key == current->smallData || key == current->largeData) {
			break;
		}
		else {
			if (key < current->smallData) {
				current = current->left;
			}
			else if (key > current->largeData) {
				current = current->right;
			}
			else {
				current = current->middle;
			}
		}
	}

	if (current == root && current->left == nullptr && current->right == nullptr) {
		if (current->largeData != "") {
			if (current->smallData == key) {
				current->smallData = current->largeData;
				current->largeData = "";
			}
			if (current->largeData == key) {
				current->largeData = "";
			}
		}
		else {
			current->smallData = "";
			root = nullptr;
		}
		return;
	}
	else if (current == root && current->left != nullptr && current->right != nullptr) {
		current->left->largeData = current->right->smallData;
		current->right = nullptr;
		root = current->left;
		current = nullptr;
		return;
	}
	//cout << "The node i need to remove from is " << current->smallData << endl;
	if (current != nullptr) {
		//cout << "Do I make it into this loop?" << endl;
		//cout << "left is " << current->left->smallData << "right is " << current->right->smallData << endl;
		if (current->left != nullptr && current->right != nullptr) {
			//cout << "How about this one" << endl;
			//Find inorder succesor
			Node* successor;
			successor = current->right;
			while (successor->left != nullptr) {
				successor = successor->left;
			}
			//cout << "My inorder successor is " << successor->smallData << endl;
			//leafNode = inorder successor
			leafNode = successor;
		}
		else {
			//cout << "Aye i made it in here instead" << endl;
			leafNode = current;
		}
		//if my leafNode has two values then I can just remove one of the data values
		

		if (leafNode->largeData != "") {
			if (key == leafNode->smallData) {
				leafNode->smallData = leafNode->largeData;
				leafNode->largeData = "";
			}
			else {
				leafNode->largeData = "";
			}
		}
		else {
			//cout << "Gotta fix my tree" << endl;
			//cout << "My root is " << root->smallData << endl;
			//cout << "Trying to fix at " << leafNode->smallData << endl;
			fix(leafNode);
		}
	}
}

void Tree::fix(Node* curr) {
	if (curr == root) {
		//cout << "Trying to fix at the root, AKA NO MORE TREE" << endl;
		if (root->left == nullptr && root->right == nullptr) {
			root = nullptr;
		}
		else {
			root->left->largeData = root->right->smallData;
			root->right = nullptr;
			root = nullptr;
		}
		
	}
	else {
		Node* parent = curr->parent;
		//cout << "My parent is " << parent->smallData << endl;
		//My parent is a 3 node
		if (parent->largeData != "") {
			if (parent->left == curr) {
				if (parent->middle->largeData != "") {
					curr->smallData = parent->smallData;
					parent->smallData = parent->middle->smallData;
					parent->middle->smallData = parent->middle->largeData;
					parent->middle->largeData = "";
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
					}
				}
				else if (parent->right->largeData != "") {
					curr->smallData = parent->smallData;
					parent->smallData = parent->middle->smallData;
					parent->middle->smallData = parent->largeData;
					parent->largeData = parent->right->smallData;
					parent->right->smallData = parent->right->largeData;
					parent->right->largeData = "";
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
					}
				}
				else {
					//merge?
					curr->smallData = parent->smallData;
					curr->largeData = parent->middle->smallData;
					parent->smallData = parent->largeData;
					parent->largeData = "";
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node

					}
					parent->middle = nullptr;
				}
			}
			else if (parent->middle == curr) {
				if (parent->left->largeData != "") {
					curr->smallData = parent->smallData;
					parent->smallData = parent->left->largeData;
					parent->left->largeData = "";
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
					}
				}
				else if (parent->right->largeData != "") {
					curr->smallData = parent->largeData;
					parent->largeData = parent->right->smallData;
					parent->right->smallData = parent->right->largeData;
					parent->right->largeData = "";
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
					}
				}
				else {
					//merge?
					parent->left->largeData = parent->smallData;
					parent->smallData = parent->largeData;
					parent->largeData = "";
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
					}
					parent->middle = nullptr;
				}
			}
			else if (parent->right == curr) {
				if (parent->middle->largeData != "") {
					curr->smallData = parent->largeData;
					parent->largeData = parent->middle->largeData;
					parent->middle->largeData = "";
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
					}
				}
				else if (parent->left->largeData != "") {
					curr->smallData = parent->largeData;
					parent->largeData = parent->middle->smallData;
					parent->middle->smallData = parent->smallData;
					parent->smallData = parent->left->largeData;
					parent->left->largeData = "";
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
					}
				}
				else {
					//merge?
					curr->largeData = parent->largeData;
					curr->smallData = parent->middle->smallData;
					parent->largeData = "";
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
					}
					parent->middle = nullptr;
				}
			}
		}
		//my parent is a two node
		else if(parent->largeData == "") {
			if (parent->right == curr) {
				if (parent->left->largeData != "") {
					curr->smallData = parent->smallData;
					parent->smallData = parent->left->largeData;
					parent->left->largeData = "";
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
						curr->left = parent->left->right;
						parent->left->right = parent->left->middle;
						parent->left->middle = nullptr;
					}
				}
				else {
					//merge?
					parent->left->largeData = parent->smallData;
					parent->smallData = "";
					//still need to reassign because now the parent is empty
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
					}
				}
			}
			else if (parent->left == curr) {
				if (parent->right->largeData != "") {
					curr->smallData = parent->smallData;
					parent->smallData = parent->right->smallData;
					parent->right->smallData = parent->right->largeData;
					parent->right->largeData = "";
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
					}
				}
				else {
					//merge?
					parent->right->largeData = parent->right->smallData;
					parent->right->smallData = parent->smallData;
					//still need to reassgin necause now parent is empty
					if (curr->left != nullptr) {
						//reassign children if you fixed at an internal node
					}
				}
			}
		}
	}
}