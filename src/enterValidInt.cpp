/*********************************************************************************** 
 * Program Name: enterValidInt.cpp
 * Author: Alexander Densmore
 * Date: 9/21/18
 * Description: Implementation file for a function that 
 * 		reads a line of user input as a string and 
 * 		tests each character to ensure input is an integer. 
 * 		Since the input is gathered from the user within
 * 		this function, it does not have any parameters.
 * 		If the user's input is not an integer, the user is prompted 
 * 		to enter a different input. If it is an integer, 
 * 		the program attempts to convert the string input to
 * 		an integer within a try-catch block and prompts the user
 * 		to enter a new integer if an exception is thrown to
 * 		ensure that the string converted to an int can be stored
 * 		in memory as an int.
 * 		Function only allows the entering of 1 integer per line.
 ********************************************************************************/

#include "enterValidInt.hpp"
using std::string;
using std::cin;
using std::cout;
using std::endl;

int enterValidInt()
{
	bool validInt = false;		// Flag to track whether valid input has been entered
	string inputAsString = "";	// user input will be gathered as part of the loop below
					// but the string is declared before the loop
					// so that it still exists after the loop.
	int inputAsInt;			// Will hold the input converted to an int
	while (!validInt)
	{
		getline(cin, inputAsString);	// accept a line of input from the user
		
		// If the user only pressed the "enter" key,
		// the input string will be empty. Use a nested
		// "while" loop to prompt the user to enter an integer.
		while (inputAsString == "")
		{
			cout << "You did not enter a valid integer. Please enter an integer: ";
			getline(cin, inputAsString);
		}

		bool validCharacters = true;	// flag to track whether each char in the input is valid for input to be an int
		
		// Check to see if character at position 0 is either a dash (negative sign) or a digit. If it is neither,
		// change validCharacters to false.
		if (!isdigit(inputAsString.at(0)) && inputAsString.at(0) != '-')
		{
			validCharacters = false;
		}

		// loop to iterate through the rest of the string
		for (int position = 1; position < inputAsString.size(); position++)	
		{
			// Check to see if character at this position is a digit. If it
			// is not a digit, set "validCharacters" flag to false. If all chars
			// in the string starting at position 1 are digits (and the char at position 0 is either a dash
			// or a digit), "validCharacters" will maintain its default
			// value of true.
			if (!isdigit(inputAsString.at(position)))
			{
				validCharacters = false;
			}
		}
		
		// After execution of "for" loop above, if all characters
		// in the string are digits, set "validInt" to "true."

		if (validCharacters)
		{
			validInt = true;
		}
		
		// Otherwise, prompt the user to enter a new input and go through the loop again.
		else
		{
			cout << "You did not enter a valid integer. Please enter an integer: ";
		}
		
		// If valid characters were entered, attempt to convert the number entered by the user to an integer.
		// If this fails, set validInt to false and prompt
		// the user to reenter the integer.
		if (validInt == true)
		{
			try
			{
				inputAsInt = stoi(inputAsString);
			}
			catch (...)
			{
				cout << "That integer is out of the range of values that can be stored in memory.\n";
				cout << "Please enter a new integer: ";
				validInt = false;
			}
		}
	}
	// Return the validated int to the calling function
	return inputAsInt;
}
