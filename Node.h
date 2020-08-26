#ifndef __NODE_H__
#define __NODE_H__


#include<iostream>
#include<string>
//#include "BSTree.h"

using namespace std;
class Node {
private:
	Node* left;
	Node* right;
	string data;
	int count;
public:
	//Node(int c = 1, Node* l = nullptr, Node* r = nullptr, string ss = "");
	Node(string);
	void setCount(int);
	int getCount();
	void setString(string);
	string getString();
	void setLeft(Node*);
	void setRight(Node*);
	Node* getLeft();
	Node* getRight();

};
#endif