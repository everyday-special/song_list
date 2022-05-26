/* Purpose: Defines the Song class
 * Author: Matthew Lidell
 * Date: 10/17/2021
 * file: song.h
 */
#pragma once
#include <cstring>
#include <iomanip>
#include <iostream>

class Song
/* Purpose: Class representing a Song. The purpose of this song is to organize song data, accessor and mutator functions for the library program.
 * This Class has 5 private data attributes:
 * 	-titlePtr - dynamically allocated c-string representing the song title
 * 	-artistPtr - dynamically allocated c-string representing the artist the song is by
 * 	-minutes - int representing the minute component of the songs duration. 0 <= minutes
 * 	-seconds - int representing the second component of the songs duration. 0 <= seconds <= 59
 * 	-likes - int representing the amount of likes the song has. 0 <= likes
 * This Class has 12 public member functions:
 * 	-Constructor taking data member values as parameters.
 * 	-Copy Constructor
 * 	-Default Destructor
 * 	-SetLikes(const int& newLikes) - sets the likes for the song to a new value.
 * 	-CompareArtist(const char queryArtist[]) - compares the artist for the song to a given artist name.
 * 	-GetTitle(char result[]) - accessor function for the title
 * 	-GetArtist(char result[]) - accessor function for the artist name
 * 	-GetMinutes() - accessor function for the minutes
 * 	-GetSeconds() - accessor function for the seconds
 * 	-GetLikes() - acccessor function for the likes
 * 	-Print() - prints the song data in an organized manner
 * 	-Overloaded < operator - compares two songs based on the amount of likes
 */ 
{
public:
	Song(const char newTitle[], const char newArtist[], const int newMin, const int newSec, const int newLikes);
	Song(const Song& refSong);
	~Song();
	void SetLikes(const int& newLikes);
	int CompareArtist(const char queryArtist[]);
	void GetTitle(char result[]);
	void GetArtist(char result[]);
	int GetMinutes();
	int GetSeconds();
	int GetLikes();
	void Print();
	bool operator<(const Song& rhs);

private:
	char* titlePtr; // Used to store the cstring representing the song's title
	char* artistPtr; // Used to store the cstring representing the song's artist
	int* minutes; // Used to store the integer representing the minute component of the songs duration
	int* seconds; // Used to store the integer representing the second component of the songs duration
	int* likes; // Used to store the integer representing the amount of a likes the song has
};
