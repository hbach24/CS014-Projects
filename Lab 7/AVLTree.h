#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <iostream>
#include "Node.h"
using namespace std;

class AVLTree {
private:
	/*Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.*/
	Node* findUnbalancedNode(Node*);

	void rotate(Node*); //this function will use rotateLeft(), rotateRight()
	void rotateLeft(Node*);
	void rotateRight(Node*);
	Node* getParentNode(Node* );

	void printBalanceFactors(Node*);

	Node* root;
	void visualizeTree(ofstream& outFS, Node* n);
	int height(Node*) const;

	void setChild(Node*, string, Node*);
	void replaceChild(Node*, Node*, Node*);
public:
	AVLTree();
	/*Insert an item to the binary search tree and perform rotation if necessary.*/
	void insert(const string&); //just going to use rotate() to maintain AVL Tree properties

	/*Return the balance factor of a given node.*/
	int balanceFactor(Node*);

	/*Traverse and print the tree in inorder notation. Print the string followed by
	its balance factor in parentheses followed by a , and one space.*/
	void printBalanceFactors();

	/*Generate dotty file and visualize the tree using dotty program. Call this function before and after rotation.*/
	void visualizeTree(const string&);


};
#endif
