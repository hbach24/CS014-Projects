#include "Playlist.h"
#include <iostream>
#include <iomanip>

using namespace std;


void outputPlaylist(string playlistTitle, PlaylistNode*& head, PlaylistNode*& tail) {
    if (head == nullptr) {
        cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
        cout << "Playlist is empty" << endl << endl;
    }
    else {
        cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
        int songNum = 1;

        for (PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
            cout << songNum << "." << endl;
            curr->PrintPlaylistNode();
            cout << endl;
            songNum++;
        }
    }
}

void addSong(PlaylistNode*& head, PlaylistNode*& tail) { //Collabed with Connie Pak
    string id;
    string name;
    string artist;
    int length;


    cout << "ADD SONG" << endl;

    cout << "Enter song's unique ID:" << endl;
    //cin.ignore();
    //getline(cin, id);
    cin >> id;
    cin.ignore();

    cout << "Enter song's name:" << endl;
    getline(cin, name);
    //cin.ignore();

    cout << "Enter artist's name:" << endl;
    getline(cin, artist);
    //cin.ignore();
    // cin.ignore();
    // cin.clear();

    cout << "Enter song's length (in seconds):" << endl;
    cin >> length;
    //cin.ignore();

    PlaylistNode* newNode = new PlaylistNode(id, name, artist, length);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->SetNext(newNode);
        tail = newNode;
    }
}

//Prompt the user for the unique ID of the song to be removed
void removeSong(PlaylistNode*& head, PlaylistNode*& tail) {
    string id;
    PlaylistNode* curr = nullptr;
    PlaylistNode* temp = nullptr;
    PlaylistNode* prev = nullptr;

    if (head == nullptr) {
        return;
    }
    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin >> id;

    curr = head;
    prev = head;
    temp = head;


    if (curr->GetID() == id) {
        // if(curr == head && head == nullptr) {
        //   return;
        // }
        if (curr == head && head->GetNext() == nullptr) {
            cout << "\"" << curr->GetSongName() << "\" removed." << endl << endl;
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
    }

    while (curr != nullptr) {
        if (curr->GetID() == id) {
            cout << "\"" << curr->GetSongName() << "\" removed." << endl << endl;
            delete curr;
            curr = nullptr;
            //prev = prev->GetNext();
            prev->SetNext(temp);
            // prev->next = temp;

            return;

        }
        else {
            prev = curr;
            //curr = curr->GetNext();
            curr = curr->GetNext(); //THIS ONE 
            if (temp != nullptr) {
                temp = curr->GetNext();
            }
        }
    }
}

void outputSong(PlaylistNode*& head, PlaylistNode*& tail) {
    string artist;

    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl;
    cin.ignore();
    getline(cin, artist);
    cout << endl;

    int songNum = 1;
    for (PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
        if (curr->GetArtistName() == artist) {
            cout << songNum << "." << endl;
            curr->PrintPlaylistNode();
            cout << endl;
        }
        songNum++;
    }
}

void outPutPlaylistTotalTime(PlaylistNode*& head, PlaylistNode*& tail) {
    int totalSeconds = 0;
    for (PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
        totalSeconds += curr->GetSongLength();
    }

    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
    cout << "Total time: " << totalSeconds << " seconds" << endl << endl;

}

// Implement the "Change position of song" menu option. Prompt the user for the current position of the song and the desired new position. Valid new positions are 1 - n (the number of nodes). If the user enters a new position that is less than 1, move the node to the position 1 (the head). If the user enters a new position greater than n, move the node to position n (the tail). 6 cases will be tested:

void changeSongPosition(PlaylistNode*& head, PlaylistNode*& tail) { //Collabed with: Jeffrey Wang

    if (head == nullptr || head->GetNext() == nullptr) {
        return;
    }

    int oldPos;
    int newPos;
    int songNum;

    PlaylistNode* oldNode = nullptr;
    PlaylistNode* newNode = nullptr;

    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;
    cin >> oldPos;
    cout << "Enter new position for song:" << endl;
    cin >> newPos;

    int count = 0;
    for (PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
        ++count; //number of songs in list
    }

    if (newPos < 1) {
        newPos = 1; //newPos is at the head
    }
    if (newPos > count) {
        newPos = count; //newPos is at the tail
    }

    //find where oldNode is at rn using oldPos
    songNum = 1;
    for (oldNode = head; oldNode != nullptr; oldNode = oldNode->GetNext()) {
        if (oldPos == songNum) {
            break;
        }
        songNum++;
    }

    if (oldPos == 1) { //if oldNode is at the head
        head = oldNode->GetNext();
    }
    else if (oldPos == count) {
        PlaylistNode* nodeBeforeOld = nullptr;
        songNum = 1;
        for (nodeBeforeOld = head; nodeBeforeOld != nullptr; nodeBeforeOld = nodeBeforeOld->GetNext()) {
            if (songNum == (oldPos - 1)) { //finding the node before oldNode
                break;
            }
            songNum++;
        }
        tail = nodeBeforeOld;
        tail->SetNext(nullptr);
    }
    else {
        PlaylistNode* nodeBeforeOld = nullptr;
        songNum = 1;
        for (nodeBeforeOld = head; nodeBeforeOld != nullptr; nodeBeforeOld = nodeBeforeOld->GetNext()) {
            if (songNum == (oldPos - 1)) { //finding the node before oldNode
                break;
            }
            songNum++;
        }
        PlaylistNode* nodeAfterOld = nullptr;
        nodeAfterOld = oldNode->GetNext();

        nodeBeforeOld->SetNext(nodeAfterOld);
    }

    songNum = 1;
    for (newNode = head; newNode != nullptr; newNode = newNode->GetNext()) {
        if (songNum == newPos) {
            break;
        }
        songNum++;
    }

    if (newPos == 1) {
        oldNode->SetNext(newNode);
        head = oldNode;

    }
    //ERRORS STARTING FROM HERE TRY TO UNDERSTAND THIS
    else if (newPos == count) {
        // oldNode->InsertAfter(newNode); //HERE?
        // tail = oldNode;
        // tail->SetNext(nullptr);
        tail->SetNext(oldNode);
        tail = oldNode;
        tail->SetNext(nullptr);
    }
    else {
        PlaylistNode* nodeBeforeNew = nullptr;
        songNum = 1;
        for (nodeBeforeNew = head; nodeBeforeNew != nullptr; nodeBeforeNew = nodeBeforeNew->GetNext()) {
            if (songNum == newPos - 1) {
                break;
            }
            ++songNum;
        }
        oldNode->SetNext(newNode);
        nodeBeforeNew->SetNext(oldNode);
    }

    //cout << getsongname << " moved to position " << newPos;

    cout << "\"" << oldNode->GetSongName() << "\" moved to position " << newPos << endl << endl;

    return;
}

void PrintMenu(const string playlistTitle, PlaylistNode*& head, PlaylistNode*& tail) { //referenced off of Professor Pendu
    char option = ' ';
    cout << playlistTitle << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl << endl;

    cout << "Choose an option:" << endl;
    cin >> option;


    // Output menu option, prompt users for valid selection
    while (option != 'q') {

        if (option == 'a') {
            addSong(head, tail);
            cout << endl;
        }

        else if (option == 'd') {
            removeSong(head, tail);
        }

        else if (option == 'c') {
            changeSongPosition(head, tail);
        }

        else if (option == 's') {
            outputSong(head, tail);
        }

        else if (option == 't') {
            outPutPlaylistTotalTime(head, tail);
        }

        else if (option == 'o') {
            outputPlaylist(playlistTitle, head, tail);
        }

        cout << playlistTitle << " PLAYLIST MENU" << endl;
        cout << "a - Add song" << endl;
        cout << "d - Remove song" << endl;
        cout << "c - Change position of song" << endl;
        cout << "s - Output songs by specific artist" << endl;
        cout << "t - Output total time of playlist (in seconds)" << endl;
        cout << "o - Output full playlist" << endl;
        cout << "q - Quit" << endl << endl;

        cout << "Choose an option:" << endl;
        cin >> option;
    }
}

int main() {
    PlaylistNode* headNode = 0;
    PlaylistNode* tailNode = 0;

    string playlistTitle;
    // Prompt user for playlist title
    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistTitle);
    cout << endl;
    // Output play list menu options
    PrintMenu(playlistTitle, headNode, tailNode);
    return 0;
}
