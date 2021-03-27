/*************************************************************************************************** 
 * Program Name: Theatrum.cpp
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
#include "Theatrum.hpp"

/*************************************************************************************************** 
 * Description: Default constructor for Theatrum object.
 *
 * 		Calls Space constructor and passes it a string indicating a space's name, 
 * 		an int indicating its number on the map, and a string with the name of a 
 * 		.txt file containing its description. 
 * 		Space constructor then sets the name and num to the parameters received.
 * 		Opens input file and reads description into description data member.
 * 		Sets all space pointers to nullptr since the mutator methods will
 * 		later be used to set those pointers once all spaces have been created.
 ***************************************************************************************************/

Theatrum::Theatrum() : Space("Theatrum", 6, "Theatrum_Description.txt")
{
}


/*************************************************************************************************** 
 * Description: Virtual destructor for Theatrum class. Body of destructor
 * 		is empty since dynamically-allocated memory for each space will be created and
 * 		destroyed by the Board class. Nonetheless, the Space parent class
 * 		and its child classes include virtual destructors so that
 * 		their destructors are called in the proper order when they
 * 		are deleted.
 ***************************************************************************************************/

Theatrum::~Theatrum()
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
 *		  - an int indicating how many steps the player has taken since bathing 
 *		  - a bool indicating whether or not the player has bathed 
 *		  - a bool indicating whether or not the player knows about the scroll that
 *		    the librarian wants to be returned 
 *		  - a bool indicating whether or not the player is still alive
 *		  - a bool indicating whether or not the player is with Nero 
 *
 *		The Theatrum's implementation of this function does the following:
 *		- Allows user to donate items from their satchel to free up space.
 *		- Does not allow user to donate scroll or permit
 ***************************************************************************************************/

void Theatrum::interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
			   bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero)
{
	// If user's satchel is empty, inform them and do not generate donation menu
	if (satchel.empty())
	{
		std::cout << "You do not have any items to donate at this time.\n";
	}

	// Otherwise, loop until the user chooses to leave or has no items left in satchel
	else
	{
		bool wantsToExit = false;
		do
		{
			// Create donation menu based on contents of user's satchel
			std::vector<std::string> donationMenu;
			std::set<std::string>::iterator satchelIter;
			for (satchelIter = satchel.begin(); satchelIter != satchel.end(); satchelIter++)
			{
				donationMenu.push_back(*satchelIter);
			}
			donationMenu.push_back("Leave the Theatrum");
			
			std::cout << "What would you like to donate to the orphans today?\n";

			// Get and process user's choice
			int donationNumber = menu(donationMenu);
			
			// If the user chooses the last menu option, set wantsToExit to true
			if (donationNumber == (donationMenu.size()))
			{
				wantsToExit = true;
			}

			// If the user has chosen to donate a key item, inform them that they cannot do so
			else if (donationMenu[(donationNumber - 1)] == SCROLL || donationMenu[(donationNumber - 1)] == PERMIT)
			{
				std::cout << "I’m sorry, but we cannot accept that item for donations\n";
			}
			
			// Otherwise, remove the requested item from the user's satchel
			else
			{
				std::string donationName = donationMenu[(donationNumber-1)];
				satchel.erase(donationName);
				std::cout << "Thank you very much! The orphans will greatly benefit from your donation.\n";
			}

			// If the user's satchel is now empty after just making the donation,
			// inform them of this before exiting the loop.
			if (satchel.empty())
			{
				std::cout << "It looks like you don’t have any items left in your satchel.\n"; 
				std::cout << "Please come back when you have more that you want to donate!\n";
			}
			std::cout << std::endl;
		} while (satchel.empty() == false && wantsToExit == false);
	}
	pressEnter();
}
