#include "IntList.h"
#include <iostream>

using namespace std;
//Collabed with Jeffrey Wang
//Initializes an empty list with dummy head and dummy tail.
IntList::IntList() {
	dummyHead = new IntNode(0);
	dummyTail = new IntNode(0);

	dummyTail->prev = dummyHead;
	dummyHead->next = dummyTail;
}

//Deallocates all remaining dynamically allocated memory (all remaining IntNodes).
IntList::~IntList() {
	IntNode* curr = dummyHead;
	IntNode* temp = new IntNode(0);

	while (curr != nullptr) {
		temp = curr->next;
		delete curr;
		curr = temp;
	}
	curr = nullptr;
}

//Inserts a data value (within a new node) at the front end of the list. This must be an O(1) operation.
void IntList::push_front(int value) {
	IntNode* newNode = new IntNode(value);
	IntNode* firstNode = new IntNode(0);

	firstNode = dummyHead->next;
	dummyHead->next = newNode;
	firstNode->prev = newNode;
	newNode->next = firstNode;
	newNode->prev = dummyHead;

}

//Removes the node at the front end of the list (the node after the dummy head). Does nothing if the list is already empty. This must be an O(1) operation.
void IntList::pop_front() {
	if (dummyHead->next == dummyTail) {
		return;
	}

	IntNode* firstNode = new IntNode(0);
	IntNode* secNode = new IntNode(0);

	firstNode = dummyHead->next;
	secNode = dummyHead->next->next; //firstNode->next;
	delete firstNode;
	dummyHead->next = secNode;
	secNode->prev = dummyHead;

}



//Inserts a data value (within a new node) at the back end of the list. This must be an O(1) operation.
void IntList::push_back(int value) {
	IntNode* lastNode = new IntNode(0);
	IntNode* newNode = new IntNode(value);

	lastNode = dummyTail->prev;
	lastNode->next = newNode;
	dummyTail->prev = newNode;
	newNode->next = dummyTail;
	newNode->prev = lastNode;

}

/*Removes the node at the back end of the list (the node before the dummy tail). 
Does nothing if the list is already empty. This must be an O(1) operation.*/
void IntList::pop_back() {
	if (dummyHead->next == dummyTail) {
		return;
	}
	IntNode* lastNode = new IntNode(0);
	IntNode* nodeBeforeLast = new IntNode(0);
	
	lastNode = dummyTail->prev; 
	nodeBeforeLast = lastNode->prev; //dummyTail = dummyTail->prev->prev;
	delete lastNode;
	nodeBeforeLast->next = dummyTail; //nodeBeforeLast now becomes the last node in the list
	dummyTail->prev = nodeBeforeLast;

}

// Returns true if the list does not store any data values (it only has dummy head and dummy tail), otherwise returns false.
bool IntList::empty() const {
	if (dummyHead->next == dummyTail) {
		return true;
	}
	else {
		return false;
	}

}
/*A global friend function that outputs to the stream all of the integer values
within the list on a single line, each separated by a space. This function does
NOT send to the stream a newline or space at the end.*/
ostream& operator<<(ostream& out, const IntList& rhs) {
	IntNode* head = new IntNode(0);
	head = rhs.dummyHead;

	//head->next == first node of list
	for (IntNode* curr = head->next; curr != rhs.dummyTail; curr = curr->next) {

		if (curr == rhs.dummyTail->prev) {
			out << curr->data; 
		}
		else {
			out << curr->data << " ";
		}
	}

	return out;
}

void IntList::printReverse() const {
	IntNode* lastNode = new IntNode(0);
	lastNode = dummyTail->prev;

	for (IntNode* curr = lastNode; curr != dummyHead; curr = curr->prev) {

		if (curr == dummyHead->next) {
			cout << curr->data;
		}
		else {
			cout << curr->data << " ";
		}
	
	}
	
}