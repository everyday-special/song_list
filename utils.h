/* Purpose: Shared utility functions for program
 * Author: Matthew Lidell
 * Date: 10/17/2021
 * file: utils.h
 */
#pragma once
#include "songlist.h"

/* Utility functions for getting and validating user input:
 * 	-getInt() - gets integer from the user. Confirms that user enters a valid integer before returning the input.
 * 	-getString() - gets string/text input from the user. Confirms that the user entered text before returning the input.
 * 	const int MAX_SIZE - global constant defining the maximum size of user input as 100 characters.
 */

const int MAX_SIZE = 100; // Maximum size of statically allocated tempory character arrays

int getInt();
void getString(char str[]);
