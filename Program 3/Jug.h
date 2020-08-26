#ifndef JUG_H
#define JUG_H
#include <list>
#include <vector>
using namespace std;

class Vertex {
public:
    //int distance; //distance from starting node
    pair<int, int> state; //<int jugAamt, int jugBamt>
    int cost; //= 0; // same as distance
    Vertex* prev;
    //list <Vertex> neighbors;
    vector<Vertex*>neighbors;
    Vertex() {
        prev = nullptr;
        pair<int, int> state(0, 0);
        cost = 0;
    }
    Vertex(pair<int, int>, int c) {
        pair<int, int> state (0, 0);
        cost = c;
        prev = nullptr;
    }
};

class Jug {
public:
    //Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA
    Jug(int, int, int, int, int, int, int, int, int);
    ~Jug();

    //solve is used to check input and find the solution if one exists
    //returns -1 if invalid inputs. solution set to empty string.
    //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    //returns 1 if solution is found and stores solution steps in solution string.
    int solve(string& solution);
private:
    //anything else you need
    int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
    //vector<Vertex> adjNodes;
    void createGraph(vector<Vertex*>&);
    vector<Vertex*> allStates; //contains all the possible combinations of both jugs

    //iterate through each state, perform all 6 actions on each state, and every time u 
    //perform an action on that state, you find it in the

    Vertex* fillJugA(Vertex*);
    Vertex* fillJugB(Vertex*);
    Vertex* emptyJugA(Vertex*);
    Vertex* emptyJugB(Vertex*);
    Vertex* pourAtoB(Vertex*);
    Vertex* pourBtoA(Vertex*);
    
    //bool validInput();
    void cheapestCost();
};

#endif

/*
bool Jug::validInput() {
    bool valid = false;
    if (!(Ca > 0 && Cb >= Ca) && !(N <= Cb && Cb <= 1000)) {
        valid = false;
    }
    if (Ca < 0 && Cb < 0 && N < 0 && cfA < 0 && cfB < 0 && ceA < 0 && ceB < 0 && cpAB < 0 && cpBA < 0) {
        return valid;
    }

    valid = true; //if all inputs are valid, then set it to true
    return valid;
    //allStates.at(0).neighbors.at(0).state.first = 1;

}*/