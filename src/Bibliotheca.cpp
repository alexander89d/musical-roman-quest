/*************************************************************************************************** 
 * Program Name: Bibliotheca.cpp
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
#include "Bibliotheca.hpp"


/*************************************************************************************************** 
 * Description: Default constructor for Bibliotheca object.
 *
 * 		Calls Space constructor and passes it a string indicating a space's name, 
 * 		an int indicating its number on the map, and a string with the name of a 
 * 		.txt file containing its description. 
 * 		Space constructor then sets the name and num to the parameters received.
 * 		Opens input file and reads description into description data member.
 * 		Sets all space pointers to nullptr since the mutator methods will
 * 		later be used to set those pointers once all spaces have been created.
 *
 * 		In addition, Bibliotheca constructor initializes private bool data member 
 * 		returnedScroll.
 ***************************************************************************************************/

Bibliotheca::Bibliotheca() : Space("Bibliotheca", 1, "Bibliotheca_Description.txt")
{
	returnedScroll = false;
}


/*************************************************************************************************** 
 * Description: Virtual destructor for Bibliotheca class. Body of destructor
 * 		is empty since dynamically-allocated memory for each space will be created and
 * 		destroyed by the Board class. Nonetheless, the Space parent class
 * 		and its child classes include virtual destructors so that
 * 		their destructors are called in the proper order when they
 * 		are deleted.
 ***************************************************************************************************/

Bibliotheca::~Bibliotheca()
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
 *		# - an int indicating how much money the player has #
 *		  - an int indicating how many steps the player has taken since bathing
 *		  - a bool indicating whether or not the player has bathed.
 *		# - a bool indicating whether or not the player knows about the scroll that
 *		    the librarian wants to be returned #
 *		  - a bool indicating whether or not the player is still alive
 *		  - a bool indicating whether or not the player is with Nero
 *
 *		The Bibliotheca's implementation of this function does the following:
 *		- If this is the user's first time in the Bibliotheca,
 *		  the librarian informs them that he wants a scroll back from the
 *		  schoolmaster. 
 *		- When they come back, he either prompts
 *		  for the scroll after that if they don't have it,
 *		  or he receives the scroll from them and gives them 5 coins.
 *		- Once the librarian has received the scroll, the library closes for the day
 *		  (during the ending sequence, the player returns with Nero,
 *		  who can enter the library whenever he pleases).
 ***************************************************************************************************/

void Bibliotheca::interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
			   bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero)
{
	// If player does not know about scroll, librarian informs them
	// that he wants it back from the schoolteacher. knowsAboutScroll reference
	// parameter is then set to true.
	if (knowsAboutScroll == false)
	{
		std::cout << "Hey, could you do me a favor? That schoolteacher over at the Ludus has not returned\n";
		std::cout << "the scroll he borrowed from here. Can you go get the scroll for me?\n";
		std::cout << "I will give you a reward if you do so.\n";
		knowsAboutScroll = true;
	}
	
	// Otherwise, if the player has not already returned the scroll and does
	// not have the scroll with them, the librarian asks for it again.
	else if (returnedScroll == false && satchel.find(SCROLL) == satchel.end()) 
	{
		std::cout << "Have you gotten that scroll from the teacher yet?\n"; 
		std::cout << "Please go and get it from him as soon as you can.\n"; 
		std::cout << "I want to close up for the day, but I will wait until you get that scroll back.\n";
	}

	// Otherwise, if the player has the scroll in their posession,
	// remove it from their satchel and have librarian thank them and give them 5 coins.
	else if (returnedScroll == false && satchel.find(SCROLL) != satchel.end())
	{
		std::cout << "Thank you for bringing that scroll back from that teacher!\n"; 
		std::cout << "He always keeps items checked out way too long.\n";
		std::cout << "Here are 5 coins for your effort.\n";
		
		money += 5;
		satchel.erase(SCROLL);
		returnedScroll = true;

		pressEnter();
		
		std::cout << "The library is now closed for the day. Have a great day!\n";
	}
	else
	{
		std::cout << "The library has closed for the day. Only those accompanied by the emperor\n"; 
		std::cout << "can enter the library when it is closed.\n";
	}

	pressEnter();
}
