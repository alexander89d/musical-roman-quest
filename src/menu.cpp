/*************************************************************************************************** 
 * Program Name: menu.cpp
 * Author: Alexander Densmore
 * Date: 10/16/18
 * Description: Implemenation file for function that is passed a string vector holding menu choices
 * 		and returns a validated menu choice as an integer. Menu is printed and input
 * 		is read within the function, and the user is repeatedly prompted
 * 		to enter valid intput until valid input is entered. Function uses
 * 		enterValidInt utility function that I created 
 * 		to make sure input is an integer, and function then tests
 * 		integer input to ensure it corresponds to one of the menu choices.
 **************************************************************************************************/
#include "menu.hpp"
using std::cout;
using std::endl;

int menu(std::vector<std::string> menuChoices)
{
	// Display stars at the top of the menu.
	cout << "\n**************************************************************************\n";
	
	// Iterate through each element of the vector and display each menu choice.
	// Auto-number each menu choice for ease of menu use.
	for (int index = 0; index < menuChoices.size(); index++)
	{
		cout << (index+1) << ". " << menuChoices[index] << endl;
	}

	// Display stars at the bottom of the menu.
	cout << "**************************************************************************\n";

	
	// Prompt the user for their menu choice. Use enterValidInt to ensure it is an
	// integer.
	cout << "\nYour choice: ";
	int menuChoiceNumber = enterValidInt();
	cout << endl;

	// If menuChoice is not within the valid range of 1 through vector size, use a "while" loop
	// to repeatedly prompt the user to enter a valid choice until one is entered.
	while (menuChoiceNumber < 1 || menuChoiceNumber > menuChoices.size())
	{
		cout << "Please enter a number between 1 and " << menuChoices.size() << ".\n";
		cout << "Your choice: ";
		menuChoiceNumber = enterValidInt();
		cout << endl;
	}

	// Return the validated menu choice to the calling function.
	return menuChoiceNumber;
}
