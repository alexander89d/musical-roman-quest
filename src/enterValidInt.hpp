/*********************************************************************************** 
 * Program Name: enterValidInt.hpp
 * Author: Alexander Densmore
 * Date: 9/21/18
 * Description: Header file for a function that 
 * 		reads a line of user input as a string and 
 * 		tests each character to ensure input is an integer. 
 * 		Since the input is gathered from the user within
 * 		this function, it does not have any parameters.
 *		If the user's input is not an integer, the user is prompted 
 * 		to enter a different input. If it is an integer, 
 * 		the program attempts to convert the string input to
 * 		an integer within a try-catch block and prompts the user
 * 		to enter a new integer if an exception is thrown to
 * 		ensure that the string converted to an int can be stored
 * 		in memory as an int.
 * 		Function only allows the entering of 1 integer per line.
 ********************************************************************************/

#ifndef ENTERVALIDINT_HPP
#define ENTERVALIDINT_HPP

#include <string>
#include <iostream>
#include <cctype>
int enterValidInt();

#endif
