#include <iostream>

#ifndef PLAYLIST_H
#define PLAYLIST_H

using namespace std;

class PlaylistNode {
  //referenced from Pendu
public:
	PlaylistNode();
	PlaylistNode(string, string, string, int, PlaylistNode* nextLoc = 0);
	void InsertAfter(PlaylistNode* nodeLoc); //
	void SetNext(PlaylistNode* ); //
	string GetID(); //
	string GetSongName(); //
	string GetArtistName() const; //
	int GetSongLength() const; //
	PlaylistNode* GetNext(); //
	void PrintPlaylistNode(); //

private:
	string uniqueID;
	string songName;
	string artistName;
	int songLength;
	PlaylistNode* nextNodePtr;



};
#endif