/* Purpose: Definition of main function
 * Author: Matthew Lidell
 * Date: 10/17/2021
 * file: main.cpp
 */
#include "main.h"

int main(int argc, char ** argv, char ** envp)
/* Purpose: Instantiate the Menu and run the menu
 * Return:
 * 	-int - returns 0 upon successful termination
 */
{
	Menu menu;

	menu.Run();
	return 0;
}
