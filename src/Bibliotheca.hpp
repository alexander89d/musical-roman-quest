/*************************************************************************************************** 
 * Program Name: Bibliotheca.hpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: Bibliotheca class that is a child of the abstract Space class. Implements the
 * 		Bibliotheca (Library). In the library, the player can learn that there is
 * 		a scroll which the librarian wants back from the schoolteacher.
 * 		If they subsequently go to the school and obtain the scroll,
 * 		the player can then receive coins (in-game currency) as a reward for returning
 * 		the scroll. This side-quest can only be completed once during a game.
 * 		During the ending if the player wins the game, the player goes
 * 		to the library with Nero (who gives the user a signed copy of the
 * 		sheet music he will be performing in the Theatrum).
 *
 * 		Protected data members inherited by Space child classes include the following:
 * 		- Pointers to the Spaces in all 8 directions (north, northeast, east, etc.)
 * 		- A string representing the name of the space
 *		- An int representing the space's number (for use when displaying map of player's
 *		current location)
 *		- A string description of the space
 *		
 *		Additional private data member of Bibliotheca class is a bool indicating
 *		whether or not the user has returned the scroll (so that the side quest is not repeated).
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
#ifndef BIBLIOTHECA_HPP
#define BIBLIOTHECA_HPP

#include "Space.hpp"

class Bibliotheca : public Space
{
	private:
		bool returnedScroll;

	public:
		Bibliotheca();
		virtual ~Bibliotheca();
		virtual void interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
				      bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero) override;
};
#endif
