#include <iostream>
#include "IntList.h"

int main() { 
	IntList list;
	cout << "empty: " << list << endl;
	list.push_front(3);
	cout << "push front 3: " << list << endl;
	list.push_front(4);
	cout << "push front 4: " << list << endl;
	list.push_back(1);
	cout << "push back 1: " << list << endl;
	list.push_back(5);
	cout << "push back5: " << list << endl;
	list.push_front(2);
	cout << "push front 2: " << list << endl;
	list.pop_back();
	cout << "pop back: " << list << endl;
	list.pop_front();
	cout << "pop front: " << list << endl;

	cout << "final list: " << list << endl;

	if (list.empty()) {
		cout << "list is empty" << endl;
	}
	else {
		cout << "list is not empty" << endl;
	}

	cout << "reversed list: ";
	list.printReverse();
	cout << endl;

	list.pop_back();
	list.pop_back();
	list.pop_front();

	if (list.empty()) {
		cout << "list is empty" << endl;
	}
	else {
		cout << "list is not empty" << endl;
	}

	list.pop_back();
	return 0;
}
