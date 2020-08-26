#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <string>
using namespace std;

template<typename T>
unsigned min_index(const vector<T>& vals, unsigned index);

template<typename T>
void selection_sort(vector<T>& vals);

template<typename T>
T getElement(vector<T> vals, int index);

/*Passes in an index of type int and a vector of type T (T could be string, double or int).
The function returns the index of the min value starting from "index" to the end of the "vector".*/
template<typename T>
unsigned min_index(const vector<T>& vals, unsigned index) {

	int minIndex = index;
	for (unsigned i = index + 1; i < vals.size(); i++) {
		if (vals.at(i) < vals.at(minIndex)) {
			minIndex = i;
		}
	}
	return minIndex;
}
/*Passes in a vector of type T and sorts them based on the selection sort
method. This function should utilize the min_index function to find the 
index of the min value in the unsorted portion of the vector.*/
  
template<typename T>
void selection_sort(vector<T>& vals) {
	//T min;
	T temp;
	unsigned minIndex;
	for (unsigned i = 0; i < vals.size(); i++) {
		minIndex = min_index(vals, i);
		//swap(vals.at(i), vals.at(min));
		temp = vals.at(i);
		vals.at(i) = vals.at(minIndex);
		vals.at(minIndex) = temp;
	}

	/*for (unsigned i = 0; i < vals.size; i++) {
		min = i;
		for (unsigned j = i + 1; j <  vals.size; j++) {
			if (vals.at(j) < vals.at(min)) {
				min = j;
			}
		}
		swap(vals.at(i), vals.at(min));
	}*/
}
//selecsort: finds the smallest item in array and then moves it to the front. after moving the smallest value to the front, it starts to search for the 
//smallest value again by starting at the index after the recently swapped value (in front)


/* Passes in a vector of type T (T could be string, double or int) and
an index of type int. The function returns the element located at the
index of the vals. You should write up a try catch block in main function
so that when the index is out of the range of the vector, the "std::outofrange"
exception will be caught by the catch (const std::outofrange& excpt). Once the 
exception is caught, it should output "out of range exception occured" followed by a new line.*/
template<typename T>
T getElement(vector<T> vals, int index) {
	return vals.at(index);
}


vector<char> createVector() {
	int vecSize = rand() % 26;
	char c = 'a';
	vector<char> vals;
	for (int i = 0; i < vecSize; i++)
	{
		vals.push_back(c);
		c++;
	}
	return vals;
}

int main() {
	vector<int> intVector;

	intVector.push_back(5);
	intVector.push_back(4);
	intVector.push_back(3);
	intVector.push_back(1);
	intVector.push_back(2);

	cout << "before sel sort intVector: " << endl;
	for (unsigned i = 0; i < intVector.size(); i++) {
		cout << intVector.at(i);
	}
	cout << endl;

	selection_sort(intVector);

	cout << "after sel sort intVector: " << endl;
	for (unsigned i = 0; i < intVector.size(); i++) {
		cout << intVector.at(i);
	}
	cout << endl << endl;

	vector<string> stringVector;

	stringVector.push_back("test");
	stringVector.push_back("test1");
	stringVector.push_back("test2");
	stringVector.push_back("test3");

	cout << "before sel sort stringVector: " << endl;
	for (unsigned i = 0; i < stringVector.size(); i++) {
		cout << stringVector.at(i) << " ";
	}
	cout << endl << endl;

	selection_sort(stringVector);

	cout << "after sel sort stringVector: " << endl;
	for (unsigned i = 0; i < stringVector.size(); i++) {
		cout << stringVector.at(i) << " ";
	}
	cout << endl;
	
	/* Passes in a vector of type T (T could be string, double or int) and
an index of type int. The function returns the element located at the
index of the vals. You should write up a try catch block in main function
so that when the index is out of the range of the vector, the "std::outofrange"
exception will be caught by the catch (const std::outofrange& excpt). Once the
exception is caught, it should output "out of range exception occured" followed by a new line.*/

//Part B
	srand(time(0));
	vector<char> vals = createVector();
	char curChar;
	unsigned int index;
	int numOfRuns = 10;
	while (--numOfRuns >= 0) {
		try {
			cout << "Enter a number: " << endl;
			cin >> index;
			if (index >= vals.size() || index < 0) {
				throw runtime_error("std::outofrange");
			}
			curChar = getElement(vals, index);
			cout << "Element located at " << index << ": is " << curChar << endl;
		}
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
			cout << "out of range exception occured" << endl;
		}
	}
	return 0;
}