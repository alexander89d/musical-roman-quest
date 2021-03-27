/*************************************************************************************************** 
 * Program Name: Thermae.cpp
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
#include "Thermae.hpp"

/*************************************************************************************************** 
 * Description: Default constructor for Thermae object.
 *
 * 		Calls Space constructor and passes it a string indicating a space's name, 
 * 		an int indicating its number on the map, and a string with the name of a 
 * 		.txt file containing its description. 
 * 		Space constructor then sets the name and num to the parameters received.
 * 		Opens input file and reads description into description data member.
 * 		Sets all space pointers to nullptr since the mutator methods will
 * 		later be used to set those pointers once all spaces have been created.
 ***************************************************************************************************/

Thermae::Thermae() : Space("Thermae", 8, "Thermae_Description.txt")
{
}


/*************************************************************************************************** 
 * Description: Virtual destructor for Thermae class. Body of destructor
 * 		is empty since dynamically-allocated memory for each space will be created and
 * 		destroyed by the Board class. Nonetheless, the Space parent class
 * 		and its child classes include virtual destructors so that
 * 		their destructors are called in the proper order when they
 * 		are deleted.
 ***************************************************************************************************/

Thermae::~Thermae()
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
 *		  - a set of strings indicating the items in the player's satchel 
 *		# - an int indicating how much money the player has #
 *		# - an int indicating how many steps the player has taken since bathing #
 *		# - a bool indicating whether or not the player has bathed #
 *		  - a bool indicating whether or not the player knows about the scroll that
 *		    the librarian wants to be returned 
 *		  - a bool indicating whether or not the player is still alive
 *		  - a bool indicating whether or not the player is with Nero 
 *
 *		The Thermae's implementation of this function does the following:
 *		- Checks to see if the user has enough money to bathe (2 coins required)
 *		- If they do, allows them to bathe or exit
 *		- If they bathe, changes values of relevant Game class variables
 *		  accordingly.
 ***************************************************************************************************/

void Thermae::interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
			   bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero)
{
	std::cout << "Welcome to the beautiful, luxurious Thermae!\n";
	std::cout << "The cost of a bath is " << BATH_COST << " coins.\n\n";
	
	// If the user does not have enough meony to bathe, inform them.
	if (money < BATH_COST)
	{
		std::cout << "You do not have enough money to bathe at this time.\n"; 
		std::cout << "Please come back again when you have more money.\n";
	}

	// Otherwise, ask the user if they want to bathe
	else
	{
		std::cout << "Would you like to bathe?\n";
		std::vector<std::string> bathMenu = {"Bathe", "Do not bathe"};
		int bathChoice = menu(bathMenu);

		// If the user chooses to bathe, deduct
		// the cost of the bath from their money, and then print the bath messages.
		if (bathChoice == 1)
		{
			money -= BATH_COST;
			
			// If the user has not bathed this game, print the
			// narration of their experience from the Thermae_Narration text file
			// and set hasBathed to true.
			if (!hasBathed)
			{
				std::ifstream inputFile("Thermae_Narration.txt");
				std::string text;
				while (getline(inputFile, text, DELIM))
				{
					std::cout << text;
				}
				hasBathed = true;
			}

			// Otherwise, if the user has already bathed this game,
			// print a shorter message.
			else
			{
				std::cout << "Since you have already bathed today, you know how the routine goes.\n";
				std::cout << "Now you are nice and clean again!\n";
			}
			
			// Reset stepsSinceBathing to 0
			stepsSinceBathing = 0;
		}

		// Otherwise, if the user has chosen not to bathe,
		// encourage them to come back again later.
		else
		{
			std::cout << "Come back later if you change your mind!\n";
		}
	}
	pressEnter();
}
