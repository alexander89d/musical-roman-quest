/*************************************************************************************************** 
 * Program Name: CircusMaximus.cpp
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
#include "CircusMaximus.hpp"

/*************************************************************************************************** 
 * Description: Default constructor for CircusMaximus object.
 *
 * 		Calls Space constructor and passes it a string indicating a space's name, 
 * 		an int indicating its number on the map, and a string with the name of a 
 * 		.txt file containing its description. 
 * 		Space constructor then sets the name and num to the parameters received.
 * 		Opens input file and reads description into description data member.
 * 		Sets all space pointers to nullptr since the mutator methods will
 * 		later be used to set those pointers once all spaces have been created.
 ***************************************************************************************************/

CircusMaximus::CircusMaximus() : Space("Circus Maximus", 4, "CircusMaximus_Description.txt")
{
}


/*************************************************************************************************** 
 * Description: Virtual destructor for CircusMaximus class. Body of destructor
 * 		is empty since dynamically-allocated memory for each space will be created and
 * 		destroyed by the Board class. Nonetheless, the Space parent class
 * 		and its child classes include virtual destructors so that
 * 		their destructors are called in the proper order when they
 * 		are deleted.
 ***************************************************************************************************/

CircusMaximus::~CircusMaximus()
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
 *		  - an int indicating how many steps the player has taken since bathing 
 *		  - a bool indicating whether or not the player has bathed 
 *		  - a bool indicating whether or not the player knows about the scroll that
 *		    the librarian wants to be returned 
 *		  - a bool indicating whether or not the player is still alive
 *		  - a bool indicating whether or not the player is with Nero 
 *
 *		The CircusMaximus's implementation of this function does the following:
 *		- If the user has money available to bet, asks
 *		  if they want to bet 2, 4, or 6 coins (only allows them
 *		  to place a given bet if they have enough coins for that bet).
 *		- Calls race function to simulate a race, get player's
 *		  pick for winning team, randmomly pick the actual winning team, and report
 *		  results.
 ***************************************************************************************************/

void CircusMaximus::interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
			   bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero)
{
	// If user does not have enough money to bet the lowest amount, inform them and ask them to come back again.
	if (money < LOW_BET)
	{
		std::cout << "I’m sorry, but you must have at least " << LOW_BET << " coins to bet on the chariot races."; 
		std::cout << "Please come back again!\n";
	}

	// Otherwise, ask how much the user wants to bet (user has been informed of the purpose
	// of this space before entering it. If they choose to enter it,
	// and they have enough money to place a bet, they must place a bet).
	else
	{
		int bet = 0;
		bool validBet = false;
		
		// Construct a menu with bet choices
		std::vector<std::string> betMenu;
		std::string betChoice = "Bet " + std::to_string(LOW_BET) + " coins.";
		betMenu.push_back(betChoice);

		betChoice = "Bet " + std::to_string(MEDIUM_BET) + " coins.";
		betMenu.push_back(betChoice);

		betChoice = "Bet " + std::to_string(HIGH_BET) + " coins.";
		betMenu.push_back(betChoice);

		// Use a do-while loop to get a valid bet from the user for which they have enough coins
		do
		{
			std::cout << "What would you like to bet?\n";
			int betChoiceNum = menu(betMenu);
			
			if (betChoiceNum == 1)	
			{
				// previous conditional already verified that player has at least 2 coins
				bet = LOW_BET;
				validBet = true;
			}
			else if (betChoiceNum == 2)
			{
				if (money >= MEDIUM_BET)
				{
					bet = MEDIUM_BET;
					validBet = true;
				}
				else
				{
					std::cout << "You don't have enough money for that bet. Please bet a lower amount.\n";
				}
			}
			else if (betChoiceNum == 3)
			{
				if (money >= HIGH_BET)
				{
					bet = HIGH_BET;
					validBet = true;
				}
				else
				{
					std::cout << "You don't have enough money for that bet. Please bet a lower amount.\n";
				}
			}

		} while(!validBet);
		
		// Deduct the bet from the player's current amount of money.
		money -= bet;

		// Call the race function, passing it the bet and adding the return value to the player's money.
		// If the player loses, the return value is 0. If they win, it is twice what they bet.
		money += race(bet);
	}

	pressEnter();
}


/*************************************************************************************************** 
 * Description: Function that simulates a chariot race. Receives an int indicating the user's bet.
 * 		Returns an int indicating how much money the user won (returns 0 if the user lost).
 ***************************************************************************************************/

int CircusMaximus::race(int bet)
{
	// Get the user's choice for what team they think will win
	std::cout << "On what team would you like to bet?\n";
	std::vector<std::string> colorMenu = {"Red", "Green", "Blue"};
	int colorChoiceNum = menu(colorMenu);
	
	// Decrement colorChoiceNum (so it corresponds to the correct enum value of the color chosen) 
	// and static_cast to Color
	colorChoiceNum--;
	Color betColor = static_cast<Color>(colorChoiceNum);

	// Randomly select the color of the winning team
	Color winnerColor = static_cast<Color>(getRandomInt(0, 2));
	
	// Report the color of the winning team
	if (winnerColor == Color::RED)
	{
		std::cout << "Red wins!\n";
	}
	else if (winnerColor == Color::GREEN)
	{
		std::cout << "Green wins!\n";
	}
	else if (winnerColor == Color::BLUE)
	{
		std::cout << "Blue wins!\n";
	}
	
	// Determine whether or not the user has won. Report the results.
	int winnings = 0;
	
	if (betColor == winnerColor)
	{
		winnings = bet * 2;
		std::cout << "Congratulations! Since you picked the winning team, you have earned " << winnings << " coins!\n";
	}
	else
	{
		std::cout << "I’m sorry, but you did not pick the winning team, so you have lost your bet.\n";
		std::cout << "Please come back and play again!\n";
	}

	return winnings;
}
