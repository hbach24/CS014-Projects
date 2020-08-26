#include "WordLadder.h"
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

/* Passes in the name of a file that contains a dictionary of 5-letter words.
      Fills the list (dict) with the words within this file.
      If the file does not open for any reason or if any word within the file
      does not have exactly 5 characters, this function should output an
      error message and return.
   */
WordLadder::WordLadder(const string& dictFile) {
    ifstream infs;
    string word;

    infs.open(dictFile.c_str());

    if (!infs.is_open()) {
        cout << "Failed to open input file: " << dictFile << endl;
        return;
    }

    while (infs >> word) {
        if (word.size() != 5) {
            cout << "Not a 5-letter word" << endl;
            return;
        }
        dict.push_back(word);
    }
    infs.close();
}

/* Passes in two 5-letter words and the name of an output file.
       Outputs to this file a word ladder that starts from the first word passed in
       and ends with the second word passed in.
       If either word passed in does not exist in the dictionary (dict),
       this function should output an error message and return.
       Otherwise, this function outputs to the file the word ladder it finds or outputs
       to the file, the message, "No Word Ladder Found."
    */
void WordLadder::outputLadder(const string& start, const string& end, const string& outputFile) {
    bool foundStart = false;
    bool foundEnd = false;

    if (start == end) {
        stack<string> sameWordStack;
        sameWordStack.push(start);
        ofstream out;
        out.open(outputFile.c_str());

        if (!out.is_open()) {
            cout << "Error opening output file: " << outputFile << endl;
            return;
        }
            out << sameWordStack.top();
            return;
    }

    list<string>::iterator it4;
    for (it4 = dict.begin(); it4 != dict.end(); it4++) {
        if (*it4 == start) {
            foundStart = true;
        }

        if (*it4 == end) {
            foundEnd = true;
        }
    }

    if (!(foundStart && foundEnd)) {
        cout << "Words not found in dictionary." << endl;
        return;
    }

    string firstWord;

    stack<string> wStack;
    wStack.push(start);

    queue<stack<string>> wordLadder;
    wordLadder.push(wStack);


    while (!wordLadder.empty()) {
        stack<string> curStack = wordLadder.front(); 
        firstWord = wordLadder.front().top();

        int diffLetters = 0;

        list<string>::iterator it = dict.begin();
        //list<string>::iterator it2 = it;

        list<string>::iterator it3;

        for (it3 = dict.begin(); it3 != dict.end(); it3++) {
            if (*it3 == start) {
                dict.erase(it3);
                break;
            }
        }
        while (it != dict.end()) { 

           // firstWord = wordLadder.front().top(); //Queue accesses the stack and after you access stack you get the first word in the stack 
            
            string dictWord = *it; //changed it to it2
           // cout << "dictWord: " << dictWord << endl;
            //cout << *it2 << endl;
            diffLetters = 0;

            for (unsigned i = 0; i < dictWord.size(); i++) {
                if (dictWord.at(i) != firstWord.at(i)) {
                    diffLetters++;
                }
                // cout << "diff" << diffLetters << endl;
            }

            if (diffLetters == 1) {
                stack<string> newStack = curStack; //new stack is a copy of front stack
                newStack.push(dictWord); //add off-by-one word to the new stack
                wordLadder.push(newStack); //enqueue this new stack to Queue
                //cout << "dictWord: " << dictWord << endl;
               

                if (dictWord == end) {
                    newStack = wordLadder.front();
                    newStack.push(end);
                    //cout << newStack.top() << "should say beads" << endl;
                    
                   
                    //cout << wordLadder.front().top() << " should say *beads*" << endl;
                   // cout << wordLadder.back().top() << " should say *beads* back" << endl;
                    ofstream outfs;
                    outfs.open(outputFile.c_str());

                    if (!outfs.is_open()) {
                        cout << "Error opening output file: " << outputFile << endl;
                        return;
                    }
                    stack<string> tempStack;
                    stack<string> finalStack;
                    tempStack = newStack;
                    
                       // cout << tempStack.top() << " should say *wince* 2" << endl;
                    while (!tempStack.empty()) {
                        finalStack.push(tempStack.top()); //wince -> heart
                        tempStack.pop();
                    }

                    while (!finalStack.empty()) {
                        outfs << finalStack.top() << " ";
                        finalStack.pop();
                    }
                   // outfs << end;
                    return;
                }
                it = dict.erase(it); //otherwise, enqueue this new Stack ^^ and remove this word from the dictionary
            }

            else {

                it++;
            }

        } //end of 2nd while loop

        wordLadder.pop(); //dequeue this front stack
    } // end of 1st while loop

    if (wordLadder.empty()) {
        ofstream outs;
        outs.open(outputFile.c_str());

        if (!outs.is_open()) {
            cout << "Failed to open output file: " << outputFile << endl;
            return;
        }
        outs << "No Word Ladder Found." << endl;

        outs.close();

        //return;
    }

} // end of function