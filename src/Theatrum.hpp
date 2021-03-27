/*************************************************************************************************** 
 * Program Name: Theatrum.hpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: Theatrum class that is a child of the abstract Space class. Implements the
 * 		Theatrum (Theater). At this space, the player can donate
 * 		unneeded items from their satchel to clear up room in their
 * 		satchel (they cannot donate the key items: scroll and permit). If the player
 * 		wins the game, they come here with Nero to record his performance as part of the
 * 		ending sequence.
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
#ifndef THEATRUM_HPP
#define THEATRUM_HPP

#include "Space.hpp"

class Theatrum : public Space
{
	public:
		Theatrum();
		virtual ~Theatrum();
		virtual void interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
				      bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero) override;
};
#endif
