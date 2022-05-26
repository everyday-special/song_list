/* Purpose: Function definitions for the Menu class
 * Author: Matthew Lidell
 * Date: 10/17/2021
 * file: menu.cpp
 */
#include "menu.h"

Menu::Menu()
/* Default Constructor for Menu.
 * Purpose: instatiates SongList list and loads songs from 'songs.txt'.
 * Parameters: None
 * Return: None
 */
{
	list = new SongList();
	LoadFromFile();
}



Menu::~Menu()
/* Default Destructor for Menu.
 * Purpose: Saves SongList list to 'songs.txt' then deletes list.
 * Parameters: None
 * Return: None
 */
{
	SaveToFile();
	delete list;
	list = nullptr;
}



void Menu::Run()
/* Run the Menu loop.
 * Purpose: Runs the menu loop of 1) printing the menu, 2) getting user selection, and 3) performing the requested action until the user quits.
 * Parameters: None
 * Return None
 */
{
	char reply; // Used to store user input

	std::cout << "Welcome to the Song Library!" << std::endl;

	do
	{
		PrintMenu();
		reply = GetReply();
		DoCommand(reply);
	}
	while (reply != 'f');
}



void Menu::PrintMenu()
/* Prints the Menu options
 * Purpose: Display the menu options for the user to select from.
 * Parameters: None
 * Return: None
 */
{
	std::cout << "\nSong Library options:" << std::endl;
	std::cout << "a) Add a new song to the Song Library." << std::endl;
	std::cout << "b) Print all songs in the Song Library." << std::endl;
	std::cout << "c) Print all songs in the Song Library by a specific artist." << std::endl;
	std::cout << "d) Edit the number of likes for a specified song." << std::endl;
	std::cout << "e) Remove all songs with less than a specified amount of likes." << std::endl;
	std::cout << "f) Quit." << std::endl;
}



const char Menu::GetReply()
/* Gets the user's menu selection
 * Purpose: Prompt the user for their selection and returns that choice.
 * Parameters: None
 * Return: char reply - character representing the users menu selection.
 */
{
	char reply; // Used to store and return user input

	std::cout << "Please make a selection (a, b, c, d, e, or f): " << std::endl;
	std::cin >> reply;
	std::cin.ignore(MAX_SIZE, '\n');
	return reply;
}



void Menu::DoCommand(const char reply)
/* Performs the command corresponding to the user's selection
 * Purpose: Performs the command corresponding to the user's selection or doing nothing in the case of invalid selection.
 * Parameters: const char reply - character representing the users menu selection.
 * Return: None
 */
{
	switch (reply)
	{
		case 'a':
			AddSong();
			break;
		case 'b':
			DisplayAllSongs();
			break;
		case 'c':
			DisplayAllSongsByArtist();
			break;
		case 'd':
			EditSongLikes();
			break;
		case 'e':
			RemoveSongsByLikes();
			break;
		case 'f':
			std::cout << "Exiting Library." << std::endl;
			break;
		default:
			std::cout << "(" << reply << ") is not a valid option. Please try again." << std::endl;
	}
}



void Menu::LoadFromFile()
/* Loads the songs from 'songs.txt' into list
 * Purpose: Attempts to load the songs from 'songs.txt' into list and notifies the user if that was unsuccessful.
 * Parameters: None
 * Return: None
 */
{
	bool ret; // Used to store return value from LoadSongsFromFile() and notify user of success or failure

	ret = (*(this->list)).LoadSongsFromFile(fileName);
	if (ret)
		std::cout << "Songs were loaded from '" << fileName << "'." << std::endl;
	else
		std::cout << "An error occurred. No songs were loaded from file." << std::endl;
}



void Menu::SaveToFile()
/* Saves the songs from list into 'songs.txt'
 * Purpose: Attempts to save the songs from list into 'songs.txt' and notifies the user if that was unsuccessful.
 * Parameters: None
 * Return: None
 */
{
	bool ret; // Used to store return value from SaveSongsToFile() and notify user of success or failure

	ret = (*(this->list)).SaveSongsToFile(fileName);
	if (ret)
		std::cout << "Songs saved to '" << fileName << "'." << std::endl;
	else
		std::cout << "An error occurred. Songs were not saved to file." << std::endl;
}



void Menu::AddSong()
/* Adds user-specified song into list
 * Purpose: Prompts the user for the information of the song to be added and then adds that song to the list.
 * Parameters: None
 * Return: None
 */
{
	char newTitle[MAX_SIZE]; // Used to temporially store user input for the new Song's title
	char newArtist[MAX_SIZE]; // Used to temportially store user input for the new Song's artist
	int newMin; // Used to store the user input for the minute component of the new Song's duration
	int newSec; // Used to store the user input for the second component of the new Song's duration
	int newLikes; // Used to store the user input for the amount of likes the new Song has

	std::cout << std::endl;
	std::cout << "Please enter the song title: ";
	getString(newTitle);
	std::cout << "Please enter the song's artist: ";
	getString(newArtist);
	std::cout << "Please enter the minute component of the song's duration (an integer 0 or greater): ";
	newMin = getInt();
	while (newMin < 0)
	{
		std::cout << "Minutes cannot be less than 0. Please try again: ";
		newMin = getInt();
	}
	std::cout << "Please enter the seconds component of the song's duration (an integer from 0 to 59, inclusive): ";
	newSec = getInt();
	while (newSec < 0 || newSec >= 60)
	{
		std::cout << "Seconds must be an integer between 0 and 59 (inclusive). Please try again: ";
		newSec = getInt();
	}
	std::cout << "Please enter the number of likes the song has (an integer 0 or great): ";
	newLikes = getInt();
	while (newLikes < 0)
	{
		std::cout << "Number of likes cannot be less than 0. Please try again: ";
		newLikes = getInt();
	}
	Song newSong = Song(newTitle, newArtist, newMin, newSec, newLikes);
	(*(this->list)).AddSong(newSong);
	std::cout << "\nSong added successfully.\n" << std::endl;
}



void Menu::DisplayAllSongs()
/* Displays all the songs in list
 * Purpose: Displays all the songs in list or notify the user that the list is empty.
 * Parameters: None
 * Return: None
 */
{
	bool ret; // Used to store the return value of PrintAll() in the case there are no songs in the list

	std::cout << "\nSong Library:" << std::endl;
	ret = (*(this->list)).PrintAll();
	if (!ret)
		std::cout << "\nThere are no songs in the Song Library." << std::endl;
}



void Menu::DisplayAllSongsByArtist()
/* Displays all the songs by a specified artist
 * Purpose: Prompts the user for an artist name. Then displays all the songs in list by that artist or notifies the user that no songs by the artist are in list.
 * Parameters: None
 * Return: None
 */
{
	bool ret; // Used to store the return value of PrintAllByArtist in the case there are no songs by the artist in the list
	char query[MAX_SIZE]; // Used to store the name of the artist to search the list by

	if ((*list).GetSize() > 0)
	{
		std::cout << "\nPlease enter the artist you wish to search the library for: ";
		getString(query);

		ret = (*(this->list)).PrintAllByArtist(query);
		if (!ret)
			std::cout << "\nThere are no songs by '" << query << "' in the Song Library." << std::endl;
	}
	else
		std::cout << "\nThere are no songs in the Song Library." << std::endl;
}



void Menu::EditSongLikes()
/* Edits the likes of a user-specified song
 * Purpose: Prints list and then asks the user for the index of the song to be edited. Then asks user for the new amount of likes for that song. Then edits that songs like and places in its correct place in the list.
 * Parameters: None
 * Return: None
 */
{
	bool ret; // Used to store the return value of list operations to for program flow control
	int index; // Used to store the index of the Song to be edited
	int newLikes; // Used to store the amount of likes the song should be changed to

	if ((*list).GetSize() > 0)
	{
		std::cout << "\nSong Library:" << std::endl;
		(*(this->list)).PrintAll();
		std::cout << "\nPlease enter the index of the song whose likes you wish to change: ";
		index = getInt();
		while (index < 0 || index >= (*(this->list)).GetSize())
		{
			std::cout << "Invalid index. Please enter a number between 0 and " << (*(this->list)).GetSize() - 1 << " (inclusive): ";
			index = getInt();
		}
		std::cout <<"Please enter the new amount of likes for the song at index " << index << ": ";
		newLikes = getInt();
		while (newLikes < 0)
		{
			std::cout << "Amount of likes for a song must be greater than or equal to 0. Please try again: ";
			newLikes = getInt();
		}
		ret = (*(this->list)).EditLikes(index, newLikes);
		if (ret)
			std::cout << "List updated." << std::endl;
		else
			std::cout << "List was not updated. Please try again." << std::endl;
	}
	else
		std::cout << "\nThe list is empty. There are no Songs to edit." << std::endl;
}



void Menu::RemoveSongsByLikes()
/* Removes all songs with less than or equal to a certain amount of likes
 * Purpose: Prompts the user for the minimum like cutoff. Then removes all songs with less likes than that.
 * Parameters: None
 * Return: None
 */
{
	int minLikes; // Used to store the like cutoff for the list
	int songsRemoved; // Used to store and return the amount of songs removed from the list
	
	if ((*list).GetSize() > 0)
	{
		std::cout << "\nPlease enter the minimum number of likes for the Song Library. All songs with likes less than or equal to this number will be removed: ";
		minLikes = getInt();
		while (minLikes < 0)
		{
			std::cout << "Amount of likes must be greater than or equal to 0. Please try again: ";
			minLikes = getInt();
		}
		songsRemoved = (*(this->list)).RemoveSongsByLikes(minLikes);
		std::cout << '\n' << songsRemoved << " songs were removed from the list." << std::endl;
	}
	else
		std::cout << "\nThe list is empty. There are no songs to be removed." << std::endl;
}
