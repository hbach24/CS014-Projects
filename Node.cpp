#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(string ss) {
	count = 1;
	left = nullptr;
	right = nullptr;
	data = ss;
}
void Node::setCount(int c) {
	this->count = c;
}

int Node::getCount() {
	return this->count;
}

void Node::setString(string ss) {
	this->data = ss;
}

string Node::getString() {
	return this->data;
}

void Node::setLeft(Node* l) {
	left = l;
}

Node* Node::getLeft() {
	return this->left;
}

void Node::setRight(Node* r) {
	right = r;
}

Node* Node::getRight() {
	return this->right;
}