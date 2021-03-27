/*************************************************************************************************** 
 * Program Name: CircusMaximus.hpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: CircusMaximus class that is a child of the abstract Space class. Implements the
 * 		CircusMaximus (Racetrack). This space allows the player to bet
 * 		coins (in-game currency) on chariot races.
 *
 * 		Protected data members inherited by Space child classes include the following:
 * 		- Pointers to the Spaces in all 8 directions (north, northeast, east, etc.)
 * 		- A string representing the name of the space
 *		- An int representing the space's number (for use when displaying map of player's
 *		current location)
 *		- A string description of the space
 *		
 *		Enum class declared in CircusMaximus header file
 *		lists the colors of the three diferent chariot teams
 *		on which the player can bet.
 *
 *		Functions inherited from parent Space class include:
 *		- Accessor and mutator methods for all space pointers
 *		- Accessor methods for space name, number, and description
 *		
 *		Public member functions of this class include:
 *		- A constructor and destructor
 *		- The implementation of the interact function (a pure virtual function in the
 *		parent class)
 *
 *		In addition, there is a private member function that simulates an individual race.
 **************************************************************************************************/
#ifndef CIRCUSMAXIMUS_HPP
#define CIRCUSMAXIMUS_HPP

#include "Space.hpp"

// Constants used by CircusMaximus class
const int LOW_BET = 2;
const int MEDIUM_BET = 4;
const int HIGH_BET = 6;

// Enum that defines Color data type (representing colors of chariot teams)
enum class Color{RED, GREEN, BLUE};

class CircusMaximus : public Space
{
	private:
		int race(int bet);
	public:
		CircusMaximus();
		virtual ~CircusMaximus();
		virtual void interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
				      bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero) override;
};
#endif
