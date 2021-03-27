/*************************************************************************************************** 
 * Program Name: DomusAurea.cpp
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
#include "DomusAurea.hpp"

/*************************************************************************************************** 
 * Description: Default constructor for DomusAurea object.
 *
 * 		Calls Space constructor and passes it a string indicating a space's name, 
 * 		an int indicating its number on the map, and a string with the name of a 
 * 		.txt file containing its description. 
 * 		Space constructor then sets the name and num to the parameters received.
 * 		Opens input file and reads description into description data member.
 * 		Sets all space pointers to nullptr since the mutator methods will
 * 		later be used to set those pointers once all spaces have been created.
 ***************************************************************************************************/

DomusAurea::DomusAurea() : Space("Domus Aurea", 2, "DomusAurea_Description.txt")
{
}


/*************************************************************************************************** 
 * Description: Virtual destructor for DomusAurea class. Body of destructor
 * 		is empty since dynamically-allocated memory for each space will be created and
 * 		destroyed by the Board class. Nonetheless, the Space parent class
 * 		and its child classes include virtual destructors so that
 * 		their destructors are called in the proper order when they
 * 		are deleted.
 ***************************************************************************************************/

DomusAurea::~DomusAurea()
{
}


/*************************************************************************************************** 
 * Description: Virtual function that implements pure virtual "interact" function
 * 		defined in parent class. Since function signature must be identical
 * 		in all child classes in order to override the parent class pure virtual function,
 * 		all child classes' interact functions receive the same seven paremeters passed by
 * 		the Game class. All parameters are passed by reference so that the 
 * 		interact functions can change them as needed (they all have return type of void 
 * 		but may need to change multiple parameters of multiple types). 
 * 		Not every child class uses all seven parameters, but each
 * 		parameter is used by at least one child class. The parameters are listed below,
 * 		with a # symbol before and after each one used by this particular class:
 *		
 *		# - a set of strings indicating the items in the player's satchel #
 *		  - an int indicating how much money the player has 
 *		# - an int indicating how many steps the player has taken since bathing #
 *		# - a bool indicating whether or not the player has bathed #
 *		  - a bool indicating whether or not the player knows about the scroll that
 *		    the librarian wants to be returned 
 *		  - a bool indicating whether or not the player is still alive
 *		# - a bool indicating whether or not the player is with Nero #
 *
 *		The DomusAurea's implementation of this function does the following:
 *		- Checks to see if the user has the permit to visit Nero
 *		- If so, checks to see if they have bathed this game
 *		- If so, checks to see if they've bathed within the last 2 turns
 *		- If so, sets "withNero" to true, triggering game ending sequence,
 *		  and user has officially won the game.
 ***************************************************************************************************/

void DomusAurea::interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
			   bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero)
{
	// If user does not have permit, inform them that they need one.
	if (satchel.find(PERMIT) == satchel.end())	// if user does not have a permit to see Nero
	{
		std::cout << "Halt! You must have a permit to see the emperor, which you can only get\n"; 
		std::cout << "from his Praetorian Prefect. The prefect is currently at the Campus Martius training.\n"; 
		std::cout << "Only come back if you have a permit!\n";
	}
	
	// Otherwise, if player has not bathed this game, insult them and tell
	// them that they must do so.
	else if (!hasBathed)
	{
		std::cout << "You smell like you have never bathed in your life!\n"; 
		std::cout << "Maybe you’re from out of town and have never used baths with the refinement of Rome’s Thermae.\n"; 
		std::cout << "Although you have a permit, I can’t let you in smelling like a barbarian!\n"; 
		std::cout << "Only come back when you have bathed!\n";
	}
	
	// Otherwise, if it has been more than 2 steps since the player bathed,
	// tell them that they need to bathe again
	else if (stepsSinceBathing > 2)
	{
		std::cout << "You stink! You say you already bathed today? I don’t care!\n"; 
		std::cout << "You must have been roaming around Rome too long since your bath.\n"; 
		std::cout << "Although you have a permit, there’s no way I’m letting you in smelling like this!\n"; 
		std::cout << "Go get a bath, and come straight back here without making any unnecessary stops along the way.\n";
	}

	// Otherwise, if the user has met all of the previously tested for requirements,
	// allow them to see Nero and set withNero to true.
	else
	{
		std::cout << "I see that you have a permit and are freshly bathed. Welcome to the Domus Aurea!\n";
		std::cout << "His Excellency awaits.\n";
		withNero = true;
	}

	pressEnter();
}
