/*************************************************************************************************** 
 * Program Name: menu.hpp
 * Author: Alexander Densmore
 * Date: 10/16/18
 * Description: Header file for function that is passed a string vector holding menu choices
 * 		and returns a validated menu choice as an integer. Menu is printed and input
 * 		is read within the function, and the user is repeatedly prompted
 * 		to enter valid intput until valid input is entered. Function uses
 * 		enterValidInt utility function that I created 
 * 		to make sure input is an integer, and function then tests
 * 		integer input to ensure it corresponds to one of the menu choices.
 **************************************************************************************************/
#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include "enterValidInt.hpp"

int menu(std::vector<std::string> menuChoices);

#endif
