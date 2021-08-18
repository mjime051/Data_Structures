#include "pch.h"
#include "arithmeticExpression.h"

arithmeticExpression::arithmeticExpression(const string &expression) {
	infixExpression = expression;
	root = nullptr;
}

void arithmeticExpression::buildTree() {
	//TODO:Later
}

void arithmeticExpression::infix() {
	TreeNode* current = root;
	infix(current);
}

void arithmeticExpression::infix(TreeNode* curr) {
	TreeNode* current = curr;
	if (current != nullptr) {
		infix(current->left);
		cout << current->data;
		infix(current->right);
	}
}

void arithmeticExpression::prefix() {
	TreeNode* current = root;
	prefix(current);
}

void arithmeticExpression::prefix(TreeNode* curr) {
	TreeNode* current = curr;
	if (current != nullptr) {
		cout << current->data;
		prefix(current->left);
		prefix(current->right);
	}
}

void arithmeticExpression::postfix() {
	TreeNode* current = root;
	postfix(current);
}

void arithmeticExpression::postfix(TreeNode* curr) {
	TreeNode* current = curr;
	if (current != nullptr) {
		postfix(current->left);
		postfix(current->right);
		cout << current->data;
	}
}

int arithmeticExpression::priority(char op) {
	int priority = 0;
	if (op == '(') {
		priority = 3;
	}
	else if (op == '*' || op == '/') {
		priority = 2;
	}
	else if (op == '+' || op == '-') {
		priority = 1;
	}
	return priority;
}

string arithmeticExpression::infix_to_postfix() {
	stack<char> s;
	ostringstream oss;
	char c;
	for (unsigned i = 0; i < infixExpression.size(); ++i) {
		c = infixExpression.at(i);
		if (c == ' ') {
			continue;
		}
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') { //c is an operator
			if (c == '(') {
				s.push(c);
			}
			else if (c == ')') {
				while (s.top() != '(') {
					oss << s.top();
					s.pop();
				}
				s.pop();
			}
			else {
				while (!s.empty() && priority(c) <= priority(s.top())) {
					if (s.top() == '(') {
						break;
					}
					oss << s.top();
					s.pop();
				}
				s.push(c);
			}
		}
		else { //c is an operand
			oss << c;
		}
	}
	while (!s.empty()) {
		oss << s.top();
		s.pop();
	}
	return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename) {
	ofstream outFS(outputFilename.c_str());
	if (!outFS.is_open()) {
		cout << "Error opening " << outputFilename << endl;
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

void arithmeticExpression::visualizeTree(ofstream &, TreeNode* curr) {
	//TODO:
}