//open your files here 
#include <iostream>
#include <string>
#include "Victim.h"

using namespace std;

int main() {
	string file;
	JCircle list;
	file = "people.txt";


	list.fillCircle(file);

	cout << "full list: " << list << endl;

	list.elimination(1, 5);

}