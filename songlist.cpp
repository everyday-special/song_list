/* Purpose: Function definitions for the SongList class
 * Author: Matthew Lidell
 * Date: 10/17/2021
 * file: songlist.cpp
 */
#include "songlist.h"

SongList::SongList()
/* Default constructor for SongList
 * Purpose: Set head to nullptr and size to 0, representing an empty list
 * Parameters: None
 * Return: None
 */
{
	head = nullptr;
	size = new int(0);
}



SongList::~SongList()
/* Default Destructor for SongList
 * Purpose: delete all the nodes and deallocate size and head data.
 * Parameters: None
 * Return: None
 */
{
	Node * curr = head;
	while(curr)
	{
		head = curr->next;
		delete curr;
		curr = head;
	}
	delete size;
	size = nullptr;
}



void SongList::AddSong(Song & newSong)
/* Purpose: Add song to the SongList in order of decreasing likes
 * Parameters:
 * 	- newSong - new Song to be added to the list
 * Return: None
 */
{
	Node * newNode = new Node(newSong);
	Add(this->head, nullptr, newNode);
	(*size)++;
}



void SongList::Add(Node * curr, Node * prev, Node * newNode)
/* Purpose: Recursive backend for adding songs to SongList
 * Parameters:
 * 	-Node * curr - pointer to current node
 * 	-Node * prev - pointer to previously visited none. nullptr if curr == head
 * 	-Node * newNode - new node to be added to the list
 * Return: None
 */
{
	if (!curr && !prev)
		this->head = newNode;
	else if (!curr && prev)
		prev->next = newNode;
	else if (*(curr->data) < *(newNode->data))
	{
		newNode->next = curr;
		if (prev)
			prev->next = newNode;
		else
			this->head = newNode;
	}
	else
		Add(curr->next, curr, newNode);
}



bool SongList::PrintAll()
/* Purpose: Print all the songs in the SongList in order of decreasing likes.
 * Parameters: None
 * Return:
 * 	-bool - true if SongList is not empty, false if SongList is empty
 */
{
	int idx = 0; // Index of the song being printed. Initialize to 0.

	return Print(this->head, idx);
}



bool SongList::Print(Node * curr, int idx)
/* Purpose: recursive backend for printing all the songs in SongList in order of decreasing likes.
 * Parameters:
 * 	- Node * curr - pointer to current node
 * 	- int idx - index of the current node (starting with 0)
 * Return:
 * 	- bool - true if SongList is not empty, false if SongList is empty
 */
{
	if (curr)
	{
		std::cout << "\nIndex: " << idx << std::endl;
		(*(curr->data)).Print();
		Print(curr->next, ++idx);
		return true;
	}
	else
		return false;
}



bool SongList::PrintAllByArtist(const char queryArtist[])
/* Purpose: Print all the songs by a specified artist in the SongList in order of decreasing likes.
 * Parameters:
 * 	- char queryArtist[] - cstring representing the artist name the SongList will be filtered by
 * Return:
 * 	- bool - true if songs by the queryArtist are found and printed, false if no songs by queryArtist are in the list
 */
{
	int idx = 0; // Index of the Song being printed. Initialized to 0.

	return PrintByArtist(this->head, queryArtist, idx, false);
}



bool SongList::PrintByArtist(Node * curr, const char queryArtist[], int idx, bool found)
/* Purpose: recursive backend for printing all the songs in SongList by artist queryArtist in order of decreasing likes.
 * Parameters:
 * 	- Node * curr - pointer to the current node
 * 	- char queryArtist[] - cstring representing the artist name the SongList is being filtered by
 * 	- int idx - index of the current node
 * 	- bool found - has a song by queryArtist been found? True if so, false if not
 * Return:
 * 	- bool - value of found. True if a song by queryArtist has been found, false if not.
 */
{
	if (!curr)
		return found;
	else if ((*curr->data).CompareArtist(queryArtist) == 0)
	{
		std::cout << "\nIndex: " << idx << std::endl;
		(*(curr->data)).Print();
		found = true;
	}
	return PrintByArtist(curr->next, queryArtist, ++idx, found);
}



int SongList::RemoveSongsByLikes(const int minLikes)
/* Purpose: Remove all songs with less than or equal to minLikes from the list
 * Parameters:
 * 	- int minLikes - integer representing the like cut off. All songs with likes greater than minLikes will be retained, all songs with less likes will be removed.
 * Return:
 * 	- int - the amount of songs that were removed from the list.
 */
{
	Node * curr = head; // pointer to current node, initialize to head (first node)
	Node * prev = nullptr; // pointer to previously visited node, initialize to nullptr since no nodes have been visited yet
	int oldSize = *(this->size); // size of the list before songs were removed

	while (curr)
	{
		if ((*(curr->data)).GetLikes() <= minLikes)
		{
			if (curr == head)
				head = nullptr;
			Node * temp = curr->next;
			if (prev)
				prev->next = nullptr;
			delete curr;
			curr = temp;
			(*size)--;

		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return oldSize - *(this->size);
}



bool SongList::EditLikes(const int index, const int newLikes)
/* Purpose: Edit change the amount of likes of the song at index index to newLikes
 * Parameters:
 * 	- int index - index of the song to be changed
 * 	- int newLikes - the value that the song at index index should be changed to
 * Return:
 * 	- bool - true if likes at index index were changed, false if no songs were modified
 */
{
	int currIdx = 0; // index of the current node. Initialized to 0.
	Node * curr = head; // Pointer to the current node, initialized to head (first node)
	Node * prev = nullptr; // Pointer to the previously visited node, initialize to nullptr since no nodes have been visited yet

	while (currIdx < *(this->size) && currIdx < index)
	{
		prev = curr;
		curr = curr->next;
		currIdx++;
	}
	if (currIdx == *(this->size))
		return false;
	else
	{
		if (!prev)
			head = curr->next;
		else
			prev->next = curr->next;
		Song newSong = Song(*(curr->data));
		delete curr;
		newSong.SetLikes(newLikes);
		Node * newNode = new Node(newSong);
		Add(this->head, nullptr, newNode);
		return true;
	}
	return false;
}



int SongList::GetSize()
/* Purpose: Accessor method for list size.
 * Parameters: None
 * Return:
 * 	- int - size of the current list
 */
{
	return *size;
}



bool SongList::LoadSongsFromFile (const char fileName[])
/* Purpose: Load songs from a specified file. File must be in the format of 1) One song per line 2) lines formatted as "titlePtr;artistPtr;minutes;seconds;likes\n"
 * Parameters:
 * 	-fileName - name of the source file to load the songs from
 * Return
 * 	- bool - true if songs were successfully loaded from the file, false if no songs were loaded due to file not existing
 */
{
	std::ifstream inFile; // file stream for loading song data
	char newTitle[MAX_SIZE]; // temporary holder for song title data
	char newArtist[MAX_SIZE]; // temporary holder for song artist data
	int min, sec, likes; // temporary holders for song minutes, seconds, and likes data

	inFile.open(fileName);
	if (!inFile)
		return false;

	inFile.get(newTitle, MAX_SIZE, ';');
	while (!inFile.eof())
	{
		inFile.get();
		inFile.get(newArtist, MAX_SIZE, ';');
		inFile.get();
		inFile >> min;
		inFile.get();
		inFile >> sec;
		inFile.get();
		inFile >> likes;
		inFile.ignore(MAX_SIZE, '\n');

		Song newSong(newTitle, newArtist, min, sec, likes);
		AddSong(newSong);

		inFile.get(newTitle, MAX_SIZE, ';');
	}
	inFile.close();
	return true;
}



bool SongList::SaveSongsToFile(const char fileName[])
/* Purpose: Save songs from SongList to file. Songs are saved in the format of 1) one song per line and 2) "titlePtr;artistPtr;minutes;seconds;likes\n"
 * Parameters:
 * 	- char fileName - name of the file to save the SongList data to.
 * Return:
 * 	- bool - true if data was saved successfully, false if not.
 */
{
	std::ofstream outFile; // file stream for saving song data
	char tempTitle[MAX_SIZE]; // temporary holder for song title data
	char tempArtist[MAX_SIZE]; // temporary holder for song artist data
	Node * curr = head; // pointer to current node. Initialized to head

	outFile.open(fileName);
	if (!outFile)
		return false;

	while (curr)
	{
		(*(curr->data)).GetTitle(tempTitle);
		(*(curr->data)).GetArtist(tempArtist);
		outFile << tempTitle << ';' << tempArtist << ';' << (*(curr->data)).GetMinutes() << ';' << (*(curr->data)).GetSeconds() << ';' << (*(curr->data)).GetLikes() << std::endl;
		curr = curr->next;
	}
	outFile.close();
	return true;
}
