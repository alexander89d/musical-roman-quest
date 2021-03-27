/*********************************************************************************** 
 * Program Name: pressEnter.cpp
 * Author: Alexander Densmore
 * Date: 9/28/18
 * Description: Implementation file for a function that 
 * 		reads a line of user input as a string and 
 * 		ensures that the user has only pressed enter. This
 * 		ensures that any "garbage input" entered by the user
 * 		when prompted to press enter will not disrupt the program
 * 		in any way. Since the input is gathered from the user within
 * 		this function, it does not have any parameters.
 * 		If the user's input is not an empty string (the user
 * 		presses anything other than enter), the user is prompted 
 * 		to press enter again. Function is exited only once the user has
 * 		pressed enter without any other input included on that line.
 * 		Since the string to hold the line of input is local in scope,
 * 		it will be destroyed when the function is exited.
 * 		Function is void since user should not be pressing anything other than
 * 		enter, and, thus, the calling function does not expect
 * 		a return value.
 ********************************************************************************/

#include "pressEnter.hpp"
using std::string;
using std::cin;
using std::cout;
using std::endl;

void pressEnter()
{
	string input = "";		// user input will be gathered as part of the loop below,
					// but the string is declared before the loop
					// so that it still exists after the loop.
	cout << "\nPress enter to continue.";
	getline(cin, input);
	cout << endl;

	// If the user did anything other than presseing enter,
	// "input" will no longer be an empty string.
	// Loop until it is an empty string.
	while (input != "")
	{
		cout << "Please do not enter any input before pressing enter. Press enter to continue.";
		getline(cin, input);
	}
}
