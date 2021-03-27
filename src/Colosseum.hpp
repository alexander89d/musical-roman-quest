/*************************************************************************************************** 
 * Program Name: Colosseum.hpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: Colosseum class that is a child of the abstract Space class. Implements the
 * 		Colosseum (Gladiators' Arena). In the Colosseum, the player
 * 		can fight gladitorial battles for the chance to win money.
 * 		They get the largest monetary reward available in the whole game
 * 		(10 coins) if they win. However, if they lose, they are at
 * 		the mercy of the presiding senator, who indicates with his thumb
 * 		whether they are to live or die. If the player loses, there is a
 * 		50% chance that they die and lose the entire game.
 *
 * 		Protected data members inherited by Space child classes include the following:
 * 		- Pointers to the Spaces in all 8 directions (north, northeast, east, etc.)
 * 		- A string representing the name of the space
 *		- An int representing the space's number (for use when displaying map of player's
 *		current location)
 *		- A string description of the space
 *		
 *		Enum class is included within the Colosseum's header file that
 *		defines Move data type (which names 3 different moves possible
 *		in a rock-paper-scissors style battle system).
 *		
 *		Additional private data member of Colosseum class is a vector of strings
 *		indicating the user's move choices.
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
#ifndef COLOSSEUM_HPP
#define COLOSSEUM_HPP

#include "Space.hpp"

// Enum class that defines 3 different moves possible in gladitorial battle system
enum class Move{SHIELD, NET, SWORD};

class Colosseum : public Space
{
	private:
		std::vector<std::string> moveMenu;
	
	public:
		Colosseum();
		virtual ~Colosseum();
		virtual void interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
				      bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero) override;
};
#endif
