#ifndef VICTIM_H
#define VICTIM_H

#include <iostream>

using namespace std;

struct Victim {
    string name;
    Victim* prev;
    Victim* next;
    Victim(string name) : name(name), prev(0), next(0) {}
};

class JCircle {
private:
    Victim* dummyHead;
    Victim* dummyTail;

public:
    JCircle();
    //~JCircle();
    void push_back(string name); //used to fill up the Josephus Circle
    void fillCircle(const string fileName);
    friend ostream& operator<<(ostream& out, const JCircle& rhs);
    void elimination(int, int);
    void deleteNode(Victim*);
};
#endif




/*#ifndef VICTIM_H
#define VICTIM_H

#include <iostream>

using namespace std;

struct Victim {
    string name;
    Victim* prev;
    Victim* next;
    Victim(string name) : name(name), prev(0), next(0) {}
};

class JCircle {
private:
    Victim* head;
    Victim* tail;

public: 
    JCircle();
    //~JCircle();
    void push_back(string name); //used to fill up the Josephus Circle
    void fillCircle(const string fileName);
    friend ostream& operator<<(ostream& out, const JCircle& rhs);
    void elimination(int, int);
    void deleteNode(Victim*);
};
#endif
*/