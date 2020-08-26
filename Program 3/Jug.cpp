#include <iostream>
#include <utility>
#include <sstream>
#include <queue>
#include <stack>
#include "Jug.h"
#include <climits>

using namespace std;
//Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA
Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
	: Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA)
{	
	for (int i = 0; i < Ca; i++) {
		for (int j = 0; j < Cb; j++) {
			Vertex newState = Vertex(pair<int,int>(i,j), 0);
			allStates.push_back(&newState);
		}
	}
	createGraph(allStates);
}

Jug::~Jug() {}

void Jug::createGraph(vector<Vertex*>& v) {
	//vector v contains all the possible states 
	//when calculating costs, consider duplicates; for ex, if(allStates.at(i).neighbors.at(i).state.first  == allStates.at(i).state.first
	//&& allStates.at(i).neighbors.at(i).state.first  == allStates.at(i).state.first) { cost = 0;}
	for (unsigned i = 0; i < v.size(); i++) {
		Vertex* newA = fillJugA(v.at(i));
		v.at(i)->neighbors.push_back(newA);

		Vertex* newB = fillJugB(v.at(i));
		v.at(i)->neighbors.push_back(newB);

		Vertex* emptyA = emptyJugA(v.at(i));
		v.at(i)->neighbors.push_back(emptyA);

		Vertex* emptyB = emptyJugB(v.at(i));
		v.at(i)->neighbors.push_back(emptyB);

		Vertex* AB = pourAtoB(v.at(i));
		v.at(i)->neighbors.push_back(AB);

		Vertex* BA = pourBtoA(v.at(i));
		v.at(i)->neighbors.push_back(BA);
	}

}

Vertex* Jug::fillJugA(Vertex* v) {
	Vertex* temp = v;
	temp->state.first = Ca;

	if ((temp->state.first == v->state.first) && (temp->state.second == v->state.second)) {
		return nullptr;
	}
	
	//temp = Vertex(pair<int, int>(Ca, int c)
	temp->cost = cfA;
	return temp;
}

Vertex* Jug::fillJugB(Vertex* v) {
	Vertex* temp = v;
	//Vertex temp1 = temp;
	temp->state.second = Cb;

	if ((temp->state.first == v->state.first) && (temp->state.second == v->state.second)) {
		return nullptr;
	}

	temp->cost = cfB;
	return temp;
}

Vertex* Jug::emptyJugA(Vertex* v) {
	Vertex* temp = v;

	temp->state.first = 0;

	if ((temp->state.first == v->state.first) && (temp->state.second == v->state.second)) {
		return nullptr;
	}

	temp->cost = ceA;
	return temp;
}

Vertex* Jug::emptyJugB(Vertex* v) {
	Vertex* temp = v;

	temp->state.second = 0;

	if ((temp->state.first == v->state.first) && (temp->state.second == v->state.second)) {
		return nullptr;
	}

	temp->cost = ceB;
	return temp;
}

Vertex* Jug::pourAtoB(Vertex* v) {
	Vertex* temp = v;
	while (temp->state.first != 0) {
		if (temp->state.second == Cb) //if jug B is already full, don't pour A into B
		{
			break; //??
		}
		temp->state.second++;
		temp->state.first--;
	}

	if ((temp->state.first == v->state.first) && (temp->state.second == v->state.second)) {
		return nullptr;
	}

	temp->cost = cpAB;
	return temp;
}

Vertex* Jug::pourBtoA(Vertex* v) {
	Vertex* temp = v;
	while (temp->state.second != 0) {
		if (temp->state.first == Ca) //if jug B is already full, don't pour A into B
		{
			break; //??
		}
		temp->state.second--;
		temp->state.first++;
	}

	if ((temp->state.first == v->state.first) && (temp->state.second == v->state.second)) {
		return nullptr;
	}

	temp->cost = cpBA;
	return temp;
}



int Jug::solve(string& solution) {
	//Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA
	solution = "";
	if (cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0) {
		return -1;
	}
	if (!(0 < Ca && Ca <= Cb)) {
		return -1;
	}
	if (!(N <= Cb && Cb <= 1000)) {
		return -1;
	}


}

void Jug::cheapestCost() {

	vector<stack<Vertex*>> sucPaths;
	
    Vertex* firstTrans;

    stack<Vertex*> allStatesStack;
	allStatesStack.push(allStates.at(0)); //push (0,0) to stack

    queue<stack<Vertex*>> statesLadder;
    statesLadder.push(allStatesStack); //push stack w/ (0,0) to queue

	int i = 0;
	while (!statesLadder.empty()) {
		stack<Vertex*> curStack = statesLadder.front(); //takes first stack in queue

		firstTrans = statesLadder.front().top(); //accesses (0,0)

		while (i < allStates.at(i)->neighbors.size()) {

			//if()
			Vertex* comb = allStates.at(i)->neighbors.at(i); //(1,0)

			if(comb != nullptr) {
				if ((comb->state.first != 0) && (comb->state.second != N)) {
					stack<Vertex*> newStack = curStack; //new stack is a copy of front stack

					Vertex* temp1 = comb->neighbors.at(i);
					if (temp1 != nullptr) {
						newStack.push(comb); //allStates.at(i)); //add off-by-one word to the new stack
						statesLadder.push(newStack); //enqueue this new stack to Queue
					}

					//if ((comb->state.first == 0) && (comb->state.second == N)) {
					if ((newStack.top()->state.first == 0) && (newStack.top()->state.second == N)) {
						newStack = statesLadder.front();
						newStack.push(comb);
						sucPaths.push_back(newStack);
					}

					stack<Vertex*> tempStack;
					stack<Vertex*> finalStack;
					tempStack = newStack;

					while (!tempStack.empty()) {
						finalStack.push(tempStack.top()); //wince -> heart
						tempStack.pop();
					}
				}
			//otherwise, enqueue this new Stack ^^ and remove this word from the dictionary
			else {

				i++;
			}

		}//end of 2nd while loop

		statesLadder.pop(); //dequeue this front stack
	}// end of 1st while loop
	/*for (unsigned i = 0; i < sucPaths.size(); i++) {
		stack<Vertex*> temp2 = sucPaths.at(i);
		for (unsigned j = 0; j < temp2.size(); j++) {
			Vertex* vtest = temp2.top();
			cout << vtest->state.first << " " << vtest->state.second << endl;
			temp2.pop();
		}
	}*/
}
