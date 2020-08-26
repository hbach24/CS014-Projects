#ifndef _STACK_H
#define _STACK_H
#include <iostream>

using namespace std;

const int MAX_SIZE = 20;

template <typename T>
class stack {
private:
	T data[MAX_SIZE];
	int size;
public:
	stack() {
		size = 0;
	}
	/*inserts a new element (val) of type T (T could be integer or string) into the data.
	If the data array is full, this function should throw an overflow_error exception
	with error message "Called push on full stack.".*/
	void push(T val) {
		try {
			if (size == MAX_SIZE) {
				throw overflow_error("Called push on full stack.");
			}
			size++;
			data[size-1] = val;
		}
		catch (overflow_error& excpt) {
			cout << excpt.what();
		}
	}

	/*removes the last element from data.If the data array is empty, this function should
	throw an outofrange exception with error message "Called pop on empty stack."*/
	void pop() {
		try {
			if (size == 0) {
				throw out_of_range("Called pop on empty stack.");
			}
			size--;
		}
		catch (out_of_range& excpt) {
			cout << excpt.what();
		}
	}

	/*returns the top element of stack(last inserted element).
	If stack is empty, this function should throw an underflow_error 
	exception with error message "Called top on empty stack.".*/

	T top() {
		T topElement;
		try {
			if (size == 0) {
				throw underflow_error("Called top on empty stack.");
			}
			//return 
			topElement = data[size - 1];
			
		}
		catch (underflow_error& excpt) {
			cout << excpt.what() << endl;
			exit(0);
			
		}
		return topElement;
	}

	//returns true if the stack is empty otherwise it returns false.
	bool empty() {
		if (size == 0) {
			return true;
		}
		else {
			return false;
		}
	}



};
#endif