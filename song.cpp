/* Purpose: Function definition for Song class
 * Author: Matthew Lidell
 * Date: 10/17/2021
 * file: song.cpp
 */
#include "song.h"

Song::Song(const char newTitle[], const char newArtist[], const int newMin, const int newSec, const int newLikes)
/* Explicity defined constructor intitializing the dynamically allocated song attributes to given data.
 * Parameters:
 * 	-newTitle - cstring with maximum size of 100 characters representing the title of the song
 * 	-newArtist - cstring with maximum size of 100 characters representing the song's artist
 * 	-newMin - integer representing the minute component of a songs duration. newMin >= 0
 * 	-newSec - integer representing the second component of a songs duration. 0 <= newSec <= 59
 * 	-newLikes - integer representing the amount of likes for the song. newLikes >= 0
 * 	Return: None
 */
{
	int strLen; // Used to store the length of the cstring so the memory can be dynamically allocated
	for (strLen = 0; newTitle[strLen] != '\0'; strLen++);
	titlePtr = new char[++strLen];
	strcpy(titlePtr, newTitle);
	for (strLen = 0; newArtist[strLen] != '\0'; strLen++);
        artistPtr = new char[++strLen];
        strcpy(artistPtr, newArtist);
	minutes = new int(newMin);
	seconds = new int(newSec);
	likes = new int(newLikes);
}



Song::Song(const Song& refSong)
/* Explicity defined copy constructor performing a deep copy of a given song.
 * Parameters:
 * 	-refSong - Song to be copied
 * Return:  None
 */
{
	int strLen; // Used to store the length of the cstring so the memory can be dynamically allocated
	strLen = strlen(refSong.titlePtr);
	this->titlePtr = new char[++strLen];
	strcpy(this->titlePtr, refSong.titlePtr);
	strLen = strlen(refSong.artistPtr);
	this->artistPtr = new char[++strLen];
	strcpy(this->artistPtr, refSong.artistPtr);
	minutes = new int(*(refSong.minutes));
	seconds = new int(*(refSong.seconds));
	likes = new int(*(refSong.likes));
}



Song::~Song()
/* Explicity defined destructor deleteing the dyamically allocated cstring pointers and assigning them to nullptr.
 * Parameters: None
 * Return: None
 */
{
	delete [] titlePtr;
	titlePtr = nullptr;
	delete [] artistPtr;
	artistPtr = nullptr;
	delete likes;
	likes = nullptr;
	delete minutes;
	minutes = nullptr;
	delete seconds;
	seconds = nullptr;
}



void Song::SetLikes(const int& newLikes)
/* Purpose: Mutator method for Song.likes
 * Parameters:
 * 	-newLikes - positive integer representing the new number of likes a song has
 * Return: None
 */
{
	*likes = newLikes;
}



int Song::GetLikes()
/* Purpose: Accessor method for Song.likes
 * Parameters: None
 * Return:
 * 	-int - number of likes for the song
*/
{
	return *likes;
}



int Song::GetMinutes()
/* Purpose: Accessor method for Song.minutes
 * Parameters: None
 * Return:
 * 	-int - minute component for the songs duration
 */
{
	return *minutes;
}



int Song::GetSeconds()
/* Purpose: Accessor method for Song.seconds
 * Parameters: None
 * Return:
 *      -int - seconds component for the songs duration
 */
{
	return *seconds;
}



void Song::GetTitle(char result[])
/* Purpose: Accessor method for cstring at Song.titlePtr
 * Parameters:
 * 	-char result[] - empty cstring with that will be populated with the song's title
 * Return: None
 */
{
	strcpy(result, titlePtr);
}



void Song::GetArtist(char result[])
/* Purpose: Accessor method for cstring at Song.artistPtr
 * Parameters:
 *      -char result[] - empty cstring with that will be populated with the song's artist
 * Return: None
 */
{
	strcpy(result, artistPtr);
}



int Song::CompareArtist(const char queryArtist[])
/* Purpose: Compares the song's artist to that of the given queryArtist
 * Parameters:
 * 	-queryArtist - c-string of max length 100 to which Song.artist will be comapred to.
 * Return:
 *	- int - result of string comparison (strcmp()) between the song's artist and the queryArtist. 0 Indicates that the artists are the same.
*/
{
	return strcmp(queryArtist, artistPtr);
}



void Song::Print()
/* Purpose: Prints Song class attributes
 * Parameters: None
 * Return: None
*/
{
	std::cout << "Title: " << titlePtr << std::endl;
	std::cout << "Artist: " << artistPtr << std::endl;
	std::cout << "Duration: " << *minutes << ":" << std::setw(2) << std::setfill('0') << *seconds << std::endl;
	std::cout << "Likes: " << *likes << std::endl;
}



bool Song::operator<(const Song& rhs)
/* Purpose: Overloaded comparison operator for Songs. Performs comparison based on song likes.
 * Parameters:
 * 	- Song rhs - Song that this song is being compared to.
 * Return: 
 * 	-bool - true if this song has less likes that rhs. false if this song has greater than or equal to likes than rhs.
 */
{
	return (*(this->likes) < *(rhs.likes));
}
