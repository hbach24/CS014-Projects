#include "Heap.h"
#include <iostream>
#include <cmath>
//Collabed with Jeffrey Wang and Skyler Saltos

using namespace std;

/*Initializes an empty heap.*/
Heap::Heap() : arr(), numItems(0) {}

/*Inserts a PrintJob to the heap without
    violating max-heap properties.*/ //slide 43, lecture 10
void Heap::enqueue(PrintJob* item) {
    if (numItems != MAX_HEAP_SIZE) {
        if (numItems == 0) {
            arr[numItems] = item;
            numItems++;
        }
        else {
            numItems++;
            arr[numItems - 1] = item;
            trickleUp(numItems - 1);

        }

    }
}

void Heap::trickleUp(int position) {
    int parent = (position - 1) / 2;
    int curr = position;
    while (curr > 0 && (arr[parent]->getPriority() < arr[curr]->getPriority())) {//position>0??
        swap(parent, curr);
        curr = parent;
        parent = (curr - 1) / 2;
    }

}
void Heap::trickleDown(int position) {
    int child = 2 * position + 1;
    PrintJob* num = arr[position];

    while (child < numItems) {
        int max = num->getPriority();
        int maxIndex = -1;
        for (int i = 0; i < 2 && i + child < numItems; i++) {
            PrintJob* currChild = arr[i + child];
            if (currChild->getPriority() > max) {
                maxIndex = i + child;
                max = arr[i + child]->getPriority();
            }
        }

        if (max == num->getPriority()) {
            return;
        }
        else {
            swap(position, maxIndex);
            position = maxIndex;
            child = 2 * position + 1;
        }
    }
}

/*Removes the node with highest priority from the heap.
  Follow the algorithm on priority-queue slides. */
void Heap::dequeue() {
   /* if (numItems == 0) {
        return;
    }
    int root = 0;
    arr[root] = arr[numItems - 1];
    numItems--;

    trickleDown(root);*/
    if (numItems == 0) {
        return;
    }
    int root = 0;
    arr[root] = arr[numItems - 1];
    numItems--;

    trickleDown(root);


}

void Heap::swap(int par, int pos) {
    PrintJob* temp = arr[par];
    arr[par] = arr[pos];
    arr[pos] = temp;
}
 
/*Prints the PrintJob with highest priority in the following format:
    Priority: priority, Job Number: jobNum, Number of Pages: numPages
    (Add a new line at the end.)*/
void Heap::print() {
    int priority = arr[0]->getPriority();
    int jobNum = arr[0]->getJobNumber();
    int numPages = arr[0]->getPages();

    cout << "Priority: " << priority << ", Job Number: " << jobNum << ", Number of Pages: " << numPages << endl;

}
/*Returns the node with highest priority.*/
PrintJob* Heap::highest() {
    return arr[0];
}









/*
old trickledown function
if (leftChild < numItems && arr[leftChild]->getPriority() > arr[parent]->getPriority()) {
        //smaller = parent;
        swap(parent, leftChild);
        trickleDown(leftChild); //trickleDown(smaller)
    }
    else if (rightChild < numItems && arr[rightChild]->getPriority() > arr[parent]->getPriority()) {
        //smaller = parent;
        swap(parent, rightChild);
        trickleDown(rightChild); // //trickleDown(smaller)
    }
    if (leftChild >= numItems || rightChild >= numItems) {
        return;
    }*/