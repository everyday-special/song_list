/* Purpose: Defines the menu class
 * Author: Matthew Lidell
 * Date: 10/17/2021
 * file: menu.h
 */
#pragma once
#include "songlist.h"
#include <fstream>

const char fileName[] = "songs.txt";

class Menu
/* UI for SongList.
 * This class has 1 private data attribute:
 * 	-list - pointer to the SongList that the user will be interacting with.
 * This Class has 3 public member functions:
 * 	-Default Constructor for instantiating the Menu class
 * 	-Default Destrutor
 * 	-Run() - Runs the main menu loop allowing the user to view and select menu options to perform operations on the SongList list
 * This Class has 10 private member functions:
 * 	-LoadFromFile() - Populates SongList with songs saved in 'songs.txt'. Tells the user if there was an issue.
 * 	-SaveToFile() - Saves SongList to 'songs.txt'. Notifies the user if there was an issue.
 * 	-PrintMenu() - Prints the main menu options for the user to see.
 * 	-GetReply() - Gets the users menu selection.
 * 	-DoCommand() - Performs the request menu operation based on the user reply.
 * 	-AddSong() - Gets song information from user and adds that song to the SongList list.
 * 	-DisplayAllSongs() - Displays all songs in the SongList list.
 * 	-DisplayAllSongsByArtist() - Gets an artist name from the user and displays all songs by that artist in the SongList list.
 * 	-EditSongLikes() - Prints the song list for user reference. Asks the user for the index of the song they'd like to edit and the new amount of likes for that song.
 * 	-RemoveSongsByLikes() - Removes all songs with less than or equal to N likes where N is user input.
 * 	*/
{
	public:
		Menu();
		~Menu();
		void Run();

	private:
		void LoadFromFile();
		void SaveToFile();
		void PrintMenu();
		const char GetReply();
		void DoCommand(const char reply);
		void AddSong();
		void DisplayAllSongs();
		void DisplayAllSongsByArtist();
		void EditSongLikes();
		void RemoveSongsByLikes();
		SongList * list; // Used to store reference to the SongList instance that this menu is operating on
};
