#include "Victim.h"
#include "fstream"

JCircle::JCircle() {
	dummyHead = new Victim("");
	dummyTail = new Victim("");

	dummyHead->next = dummyTail;
	dummyHead->prev = dummyTail;

	dummyTail->prev = dummyHead;
	dummyTail->next = dummyHead;



}

/*JCircle::~JCircle() {
	if (dummyHead->next == dummyTail) {
		return;
	}

	//Victim* curr = new Victim(0);
	for (Victim* curr = dummyHead->next; curr != dummyTail; curr = curr->next) {
		delete curr;
	}
}*/

void JCircle::push_back(string name) {
	Victim* lastNode = new Victim("");
	Victim* newNode = new Victim(name);

	lastNode = dummyTail->prev;
	lastNode->next = newNode;
	dummyTail->prev = newNode;
	newNode->next = dummyTail;
	newNode->prev = lastNode;

}

void JCircle::fillCircle(const string fileName) {
	ifstream infs;
	string name;

	infs.open(fileName);

	if (!infs.is_open()) {
		cout << "file failed to open" << endl;
		return;
	}

	while (infs >> name) {
		Victim* addPerson = new Victim(name);
		push_back(name);
	}
}

ostream& operator<<(ostream& out, const JCircle& rhs) {
	Victim* head = new Victim("");
	head = rhs.dummyHead;

	for (Victim* curr = head->next; curr != rhs.dummyTail; curr = curr->next) {

		out << curr->name;
		out << endl;
	}
	return out;
}
void JCircle::deleteNode(Victim* victim) {
	if (victim == dummyTail || victim == dummyHead) {
		return;
	}
	Victim* nodeBeforeVictim = victim->prev;
	Victim* nodeAfterVictim = victim->next;

	delete victim;
	victim = nullptr; //might be unnecessary

	nodeBeforeVictim->next = nodeAfterVictim;
	nodeAfterVictim->prev = nodeBeforeVictim;



}

void JCircle::elimination(int start, int k) {
	//cout << "wat" << endl;
	int counter = 1;
	int listSize = 0;
	Victim* temp = new Victim("");
	Victim* currNode = new Victim("");
	Victim* firstNode = new Victim("");

	int countStart = 1;
	
	for (Victim* curr = dummyHead->next; curr != dummyTail; curr = curr->next) {
		listSize++;
	}
	//size = listSize;
	//cout << listSize << " SIZE" << endl;

	for (Victim* curr = dummyHead->next; curr != dummyTail; curr = curr->next) {
		if (countStart == start) {
			firstNode = curr;
			//cout << firstNode -> name << "LOOK" << endl;
		}
		countStart++;
	}
	currNode = firstNode;
		//cout << currNode->name << "LOOOKIE" << endl;
		//what if I made a vector of victims, and deleted what needs to be deleted so I don't have to deal with dummyHead or dummyTail?
		while (listSize != 1) {
			//cout << "wat" << endl;
			counter = 1;
			while (counter <= k) { //need to fix this while condition or else it will go in an infinite loop // while(counter <= k) ? before = currNode != dummyhead
				//cout << "yo" << endl;

				if (counter == k) {
					temp = currNode;

					if (currNode == dummyTail->prev) {
						currNode = currNode->next->next->next; //skip dummyHead and dummyTail and land back on first node
					}
					else {
						currNode = currNode->next;
					}
					//cout << temp->name << "break" << endl;
					//break;
				}
				else {
					if (currNode == dummyTail->prev) {
						currNode = currNode->next->next->next; //skip dummyHead and dummyTail and land back on first node
					}
					else {
						currNode = currNode->next;
						//cout << currNode->name << "MOVE NEXT" << endl;
					}
				}
				counter++;
			}
			//	Victim* nodeAfterCurr = currNode->next; // this might be fishy lol cuz what if currNode is at the last node this will end up accessing dummyTail
			cout << temp->name << endl;
			deleteNode(temp);
			temp = nullptr;
			//currNode 
			/*if (nodeAfterCurr != dummyHead && nodeAfterCurr != dummyTail) { //maybe just need " != dummyTail"
				currNode = currNode->next;
			}*/
			//cout << "look at dis list" << endl;

		
			
			//for (Victim* curr = dummyHead->next; curr != dummyTail; curr = curr->next) {
				listSize--;
				//cout << "listSize decrement" << listSize << endl;
			//}

			/*listSize = 0;
			for (Victim* curr = dummyHead->next; curr != dummyTail; curr = curr->next) {
				listSize++;
			}*/
			//counter = 1;
		} //end of outer while loop


	 if (listSize == 1) {
			   cout << "WINNER!!!" << endl;
			   cout << dummyHead->next->name << endl; //winner!
			   return;
		   }

}

//i tested this elimination function on a list of: 1, 2, 3, 4, 5 ; k = 2
//try testing it again with a different list (size 1, size > 5, size < 5) and different k values. i think the different k values are more important
//make your deleteNode function but i dont think it'll be too bad hopefully lol
// and shit u forgot to include start node fuck so lol u can't start at the first node kms; EDIT THAT