#ifndef _NODE_H
#define _NODE_H
#include <iostream>

using namespace std;

class Node {
private:



public:
	Node(string);
	Node* left;
	Node* right;
	//Node* root;
	string data;


};
#endif