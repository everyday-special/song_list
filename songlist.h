/* Purpose: Defines the SongList class
 * Author: Matthew Lidell
 * Date: 10/17/2021
 * file: songlist.h
 */
#pragma once
#include "song.h"
#include "utils.h"
#include <fstream>

class SongList
/* SongList ADT: Singly linked list of Songs
 * This class has a privately defined struct Node representing a node in the linked list.
 * This class has 2 private data attributes:
 * 	-Node * head - pointer to the first Node in the list
 * 	-int * size - pointer to an integer represtning the size of the list
 * This class has 10 public member functions:
 * 	-Default constructor for instantiating the SongList class
 * 	-Default destructor
 * 	-AddSong(Song & newSong) - Adds newSong to the list. Inserts songs in list by amount of likes (descending)
 * 	-EditLikes - Edits the likes the song at a specified index. Reinserts the song to the new correct position based on the new amount of likes.
 * 	-PrintAll() - Prints all the songs in the list
 * 	-PintAllByArtist(const char queryArtist[]) - Prints all songs by queryArtist in the list
 * 	-RemoveSongsByLikes(const in minLikes) - Removes all songs with likes less than or equal to minLikes
 * 	-LoadSongsFromFile(const char fileName[]) - loads songs from the specified file
 * 	-SaveSongsToFile(const char fileName[]) - saves songs to the specified file
 * 	-GetSize() - returns the current size of the list.
 * This class has 3 private member functions:
 * 	-Add(Node * curr, Node * prev, Node * newNode) - recursive backend for adding songs to list
 * 	-Print(Node * curr, int idx) - recursive backend for printing all songs in the list
 * 	-PrintByArtist(Node * curr, const char queryArtist[], int idx, bool found) - recursive backend for printing all songs by a queryArtist in the list
 */ 
{
	public:
		SongList();
		~SongList();
		void AddSong(Song &  newSong);
		bool EditLikes(const int index, const int newLikes);
		bool PrintAll();
		bool PrintAllByArtist(const char queryArtist[]);
		int RemoveSongsByLikes(const int minLikes);
		bool LoadSongsFromFile(const char fileName[]);
		bool SaveSongsToFile(const char fileName[]);
		int GetSize();

	private:
		struct Node
		/* Struct representing a node in the SongList singly linked list.
		 * Node has 2 data attributes:
		 * 	- Song * data - pointer to the Song at this location in the list
		 * 	- Node * next - pointer to the next Node in the list
		 * Node has 2 member functions:
		 * 	- Constructor creating a new node where the data is the given song
		 * 	- Default Destructor
		 */
		{
			Node(Song & newSong)
			/* Purpose: Instantiate a new Node. Sets data to newSong and next to nullptr
			 * Parameters:
			 * 	- newSong - Song to be stored in this node
			 * Return None
			 */
			{
				data = new Song(newSong);
				next = nullptr;
			}
			~Node()
			/* Purpose: Destroy allocated Node and associated data attributes.
			 * Parameters: None
			 * Return: None
			 */
			{
				delete data;
				data = nullptr;
				next = nullptr;
			}
			Song * data; // Used for storing song data at this position in the list
			Node * next; // used for storing the location of the next node in the list
		};
		Node * head; // Used for storing the first node in the list
		int * size; // Used for storing the current size of the list
		void Add(Node * curr, Node * prev, Node * newNode);
		bool Print(Node * curr, int idx);
		bool PrintByArtist(Node * curr, const char queryArtist[], int idx, bool found);
};
