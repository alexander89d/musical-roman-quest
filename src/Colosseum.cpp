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
#include "Colosseum.hpp"

/*************************************************************************************************** 
 * Description: Default constructor for Colosseum object.
 *
 * 		Calls Space constructor and passes it a string indicating a space's name, 
 * 		an int indicating its number on the map, and a string with the name of a 
 * 		.txt file containing its description. 
 * 		Space constructor then sets the name and num to the parameters received.
 * 		Opens input file and reads description into description data member.
 * 		Sets all space pointers to nullptr since the mutator methods will
 * 		later be used to set those pointers once all spaces have been created.
 *
 * 		In addition, Colosseum constructor initializes
 * 		moveMenu private data member.
 ***************************************************************************************************/

Colosseum::Colosseum() : Space("Colosseum", 7, "Colosseum_Description.txt")
{
	moveMenu.push_back("Shield");
	moveMenu.push_back("Net");
	moveMenu.push_back("Sword");
}


/*************************************************************************************************** 
 * Description: Virtual destructor for Colosseum class. Body of destructor
 * 		is empty since dynamically-allocated memory for each space will be created and
 * 		destroyed by the Board class. Nonetheless, the Space parent class
 * 		and its child classes include virtual destructors so that
 * 		their destructors are called in the proper order when they
 * 		are deleted.
 ***************************************************************************************************/

Colosseum::~Colosseum()
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
 *		# - a bool indicating whether or not the player is still alive #
 *		  - a bool indicating whether or not the player is with Nero 
 *
 *		The Colosseum's implementation of this function does the following:
 *		- Implements gladitorial battles with shield, net, sword system
 *		  (like rock-paper-scissors). If user wins, they get 10 coins.
 *		- If user loses, there is a 50% chance the presiding senator lets
 *		  them live and a 50% chance he condemns them to death.
 *		- Each player starts with 5 strength points and loses a strength
 *		  point for each turn he loses. Whoever runs out of strength
 *		  points first loses the match.
 ***************************************************************************************************/

void Colosseum::interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
			   bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero)
{
	// Print rules
	std::cout << "The gladiator battle is about to begin. You each have 5 strength points\n";
	std::cout << "Whoever loses a turn loses a strength point. Whoever runs out of strength points first loses the match.\n";
	std::cout << "Remember, this is like rock, paper, scissors. Shield beats sword, sword beats net, net beats shield.\n";
	std::cout << "If you both throw the same move, that turn is a draw and no one loses strength points.\n";
	
	pressEnter();
	
	// Initialize starting strength points
	int userStrengthPoints = 5;
	int computerStrengthPoints = 5;
	
	while (userStrengthPoints > 0 && computerStrengthPoints > 0)
	{
		std::system("clear");
		std::cout << "\t\tYour strength points: " << userStrengthPoints;
		std::cout << "\t\tYour opponent's strength points: " << computerStrengthPoints << "\n\n";
		std::cout << "Select your move:\n";
		
		// Get user's move choice. Decrement so it aligns with enum value of move.
		// Static cast to move.
		int userMoveNum = menu(moveMenu);
		userMoveNum--;
		Move userMove = static_cast<Move>(userMoveNum);

		// Randomly determine computer's move
		int computerMoveNum = getRandomInt(0, 2);
		std::cout << "Your opponent’s move: " << moveMenu[computerMoveNum] << std::endl;
		Move computerMove = static_cast<Move>(computerMoveNum);
		
		// Determine winner of turn
		if (userMove == Move::SHIELD)
		{
			if (computerMove == Move::SWORD)
			{
				std::cout << "You win this round!\n";
				computerStrengthPoints--;
			}
			else if (computerMove == Move::NET)
			{
				std::cout << "Your opponent wins this round.\n";
				userStrengthPoints--;
			}
			else
			{
				std::cout << "This round is a draw.\n";
			}
		}
		else if (userMove == Move::NET)
		{
			if (computerMove == Move::SHIELD)
			{
				std::cout << "You win this round!\n";
				computerStrengthPoints--;
			}
			else if (computerMove == Move::SWORD)
			{
				std::cout << "Your opponent wins this round.\n";
				userStrengthPoints--;
			}
			else
			{
				std::cout << "This round is a draw.\n";
			}
		}
		else if (userMove == Move::SWORD)
		{
			if (computerMove == Move::NET)
			{
				std::cout << "You win this round!\n";
				computerStrengthPoints--;
			}
			else if (computerMove == Move::SHIELD)
			{
				std::cout << "Your opponent wins this round.\n";
				userStrengthPoints--;
			}
			else
			{
				std::cout << "This round is a draw.\n";
			}
		}
		pressEnter();
	}

	// Determine final outcome of match
	if (computerStrengthPoints == 0)
	{
		std::cout << "Congratulations, you win!\n";
		bool computerDies = static_cast<bool>(getRandomInt(0, 1));
		if (!computerDies)
		{
			std::cout << "The senator has ordered that you let your opponent live.\n";
		}
		else
		{
			std::cout << "The senator has ordered that you kill your opponent.\n";
		}
		
		std::cout << "Here are 10 coins for your victory.\n";
		money += 10;
	}
	
	else if (userStrengthPoints == 0)
	{
		std::cout << "You have lost this match.\n";
		bool userDies = static_cast<bool>(getRandomInt(0, 1));
		if (!userDies)
		{
			std::cout << "The senator has ordered your opponent to let you live.\n";
			std::cout << "You haven’t won any money, but you leave with your life.\n";
		}
		else
		{
			std::cout << "The senator has ordered your opponent to kill you.\n";
			std::cout << "Thank you for your sacrifice for the entertainment of the Roman People.\n";
			stillAlive = false;
		}
	}
	pressEnter();
}
