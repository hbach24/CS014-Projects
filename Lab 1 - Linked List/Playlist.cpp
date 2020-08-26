#include "Playlist.h"
#include <iostream>
#include <string>

using namespace std;

PlaylistNode::PlaylistNode() {
	uniqueID = "none";
	songName = "none";
	artistName = "none";
	songLength = 0;
	nextNodePtr = 0;
}

PlaylistNode::PlaylistNode(string id, string name, string artist, int length, PlaylistNode* nextLoc) {
	uniqueID = id;
	songName = name;
	artistName = artist;
	songLength = length;
}

void PlaylistNode::PrintPlaylistNode() {
	cout << "Unique ID: " << uniqueID << endl;
	cout << "Song Name: " << songName << endl;
	cout << "Artist Name: " << artistName << endl;
	cout << "Song Length (in seconds): " << songLength << endl;
}

void PlaylistNode::InsertAfter(PlaylistNode* nodeLocation) { //referenced from zyBooks 
	PlaylistNode* tempNxt = nullptr;

	tempNxt = this->nextNodePtr;
	this->nextNodePtr = nodeLocation;
	nodeLocation->nextNodePtr = tempNxt;
}

void PlaylistNode::SetNext(PlaylistNode* nextNode) {
	this->nextNodePtr = nextNode;
}

string PlaylistNode::GetID() {
	return uniqueID;
}

string PlaylistNode::GetSongName() {
	return songName;
}

string PlaylistNode::GetArtistName() const{
	return artistName;
}

int PlaylistNode::GetSongLength() const {
	return songLength;
}

PlaylistNode* PlaylistNode::GetNext() {
	return this->nextNodePtr;
}