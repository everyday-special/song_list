/* Purpose: Definition of shared utility functions for program
 * Author: Matthew Lidell
 * Date: 10/17/2021
 * file: utils.cpp
 */
#include "utils.h"

int getInt()
/*
        Purpose: Read and return a valid integer from user input
        Parameters: None
        Return: int integer
*/
{
	int integer; // Used to store and return user input

	std::cin >> integer;
	while(!std::cin)
	{
		std::cin.clear();
		std::cin.ignore(MAX_SIZE, '\n');
		std::cout << "An illegal integer was entered. Please try again: ";
		std::cin >> integer;
	}
	std::cin.ignore(MAX_SIZE, '\n');
	return integer;
}

void getString(char str[])
{
/*
Purpose: Keeps prompting user to enter a valid string until one is entered.
Parameters:
char str[] - cstring of size maxSize that holds the user input
Return: None
*/

	std::cin.get(str, MAX_SIZE, '\n');
	while (!std::cin)
	{
		std::cin.clear();
		std::cin.ignore(MAX_SIZE, '\n');
		std::cout << "No characters were entered. Please try again: ";
		std::cin.get(str, MAX_SIZE, '\n');
	}
	std::cin.ignore(MAX_SIZE, '\n');
}
