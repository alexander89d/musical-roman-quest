/*************************************************************************************************** 
 * Program Name: Thermae.hpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: Thermae class that is a child of the abstract Space class. Implements the
 * 		Thermae (Baths). At this space, the player can take a bath for 2 coins.
 * 		It is required that the player bathe no more than 2 steps before gaining
 * 		entry to the Domus Aurea (palace). This is exactly the number of steps
 * 		to get from the Thermae to the Domus Aurea if the player takes the shortest
 * 		route possible (by going through the Forum).
 *
 * 		Protected data members inherited by Space child classes include the following:
 * 		- Pointers to the Spaces in all 8 directions (north, northeast, east, etc.)
 * 		- A string representing the name of the space
 *		- An int representing the space's number (for use when displaying map of player's
 *		current location)
 *		- A string description of the space
 *
 *		Functions inherited from parent Space class include:
 *		- Accessor and mutator methods for all space pointers
 *		- Accessor methods for space name, number, and description
 *		
 *		Member functions of this class include:
 *		- A constructor and destructor
 *		- The implementation of the interact function (a pure virtual function in the
 *		parent class)
 **************************************************************************************************/
#ifndef THERMAE_HPP
#define THERMAE_HPP

#include "Space.hpp"

// Constant indicating the cost of a bath
const int BATH_COST = 2;

class Thermae : public Space
{
	public:
		Thermae();
		virtual ~Thermae();
		virtual void interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
				      bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero) override;
};
#endif
