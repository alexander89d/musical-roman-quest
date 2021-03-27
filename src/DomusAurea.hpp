/*************************************************************************************************** 
 * Program Name: DomusAurea.hpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: DomusAurea class that is a child of the abstract Space class. Implements the
 * 		DomusAurea (Nero's Palace). The player visits the DomusAurea
 * 		when they are ready to visit Nero. In order to be granted permission,
 * 		they must have obtained the permit from the Campus Martius and must
 * 		have bathed within the last 2 time steps. Once the player receives permission
 * 		from the palace guard to visit Nero, they win the game, and the game ending
 * 		sequence is triggered by the Game class.
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
#ifndef DOMUSAUREA_HPP
#define DOMUSAUREA_HPP

#include "Space.hpp"

class DomusAurea : public Space
{
	public:
		DomusAurea();
		virtual ~DomusAurea();
		virtual void interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
				      bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero) override;
};
#endif
