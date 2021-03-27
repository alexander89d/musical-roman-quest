/*************************************************************************************************** 
 * Program Name: Game.cpp
 * Author: Alexander Densmore
 * Date: 12/4/18
 * Description: Class that instantiates a Game object representing
 * 		an individual game of the Ancient Rome-themed board game.
 *
 * 		Private data members include the following:
 * 		- A Board object representing the game's board
 * 		- A set of strings representing the items the player is carrying in their satchel
 * 		- An integer representing how many coins (in-game currency) the user has
 * 		- An integer representing the number of steps the player has taken since the start 
 * 		  of the game
 * 		- An integer representing the number of steps the player has taken since bathing
 * 		- A bool representing whether or not the player has bathed at the Thermae space
 * 		- A bool indicating whether or not the player knows about the scroll
 * 		  that the librarian wants the school teacher to return
 * 		- A bool indicating whether or not the player is still alive
 * 		- A bool indicating whether or not the player is with Nero (tiggers winning ending 
 * 		  sequence when its value is true)
 * 		- A bool indicating whether or not the game is over (set to true when the
 * 		  player wins, dies, or runs out of time steps; accessor method
 * 		  allows outside functions to check whether or not the game is over)
 *		
 *		Public member functions include the following:
 *		- A constructor
 *		- A function that executs a turn in the game
 *		- An accessor function that returns a bool to indicate whether or not the game is 
 *		  over
 *
 *		Private member functions include the following:
 *		- A function that prints the current contents of the player's satchel
 *		  (or a message indicating that the satchel is empty)
 *		- A function that reads in and displays the end-of-game messages and text-based
 *		  images from a text file that are displayed when the player wins the game
 *		  (by gaining access to Nero at the Domus Aurea)
 ***************************************************************************************************/
#include "Game.hpp"


/***************************************************************************************************** 
 * Description: Default constructor that initializes the data members of the Game.
 * 		
 * 		The Board is not explicitly initialized in the constructor
 * 		because it is initialized by its default constructor
 * 		when a Game object is instantiated.
 *
 * 		The player's satchel starts out empty, so no strings are added to the set in this
 * 		constructor.
 ****************************************************************************************************/

Game::Game()
{
	money = 0;
	stepsTaken = 0;
	stepsSinceBathing = 0;
	hasBathed = false;
	knowsAboutScroll = false;
	stillAlive = true;
	withNero = false;
	gameOver = false;
}


/*************************************************************************************************** 
 * Description: Function that executes a turn in the game. First, the user is asked
 * 		if they would like to "enter" the space at which they are currently
 * 		located (if they choose yes, the space's "interact" function is called).
 * 		After the user is done with the interaction (or if they choose not
 * 		to enter the space), it is determined whether or not the game is over (based
 * 		on whether or not the player is still alive, whether they have steps remaining, and
 * 		whether or not they are with Nero and have therefore won the game). Receives and
 * 		returns nothing.
 ****************************************************************************************************/

void Game::take_turn()
{	
	// Determine the user's current space and save in a pointer variable to be referred to again
	// throughout this function
	Space* currentSpace = gameBoard.get_player_location();
		
	// Clear the screen for the new turn. At the top of the new screen,
	// print steps taken of steps allowed, number of coins, satchel contents, and the board image indicating
	// where the player is located.
	std::system("clear");
	std::cout << "\tSteps Taken: " << stepsTaken << " of " << MAX_STEPS;
	std::cout << "\tCoins: " << money;
	std::cout << "\tCurrent Space: " << currentSpace->get_name() << std::endl << std::endl;
	print_satchel_contents();
	gameBoard.print_board();

	// Display the description of the space at which the player is located
	std::cout << "Space Description: " << currentSpace->get_description();
	
	// Determine whether the user wants to enter (i.e. interact with) the current space
	// or keep moving.
	std::string enterSpace = "Enter " + currentSpace->get_name();
	std::vector<std::string> enterMenu = {enterSpace, "Keep moving"};
	int enterChoice = menu(enterMenu);

	// If the user has chosen to enter the space, call the space's "interact" function,
	// and process any outcomes based on changed values of reference variables
	if (enterChoice == 1)
	{
		// Clear screen, print the space name, the number of coins the user has, and the satchel contents
		std::system("clear");
		std::cout << "\t\tCurrent Space: " << currentSpace->get_name();
		std::cout << "\t\tCoins: " << money << std::endl << std::endl;
		print_satchel_contents();
		std::cout << std::endl << std::endl;

		// Call the current space's interact function
		currentSpace->interact(satchel, money, stepsSinceBathing, hasBathed, knowsAboutScroll, stillAlive, withNero);
		
		// If the user is with Nero after interacting with this space,
		// they have won the game. Call ending_sequence to print the ending.
		if (withNero)
		{
			ending_sequence();
		}

		// Otherwise, test to see if the player is still alive (if they are with Nero in the condition above,
		// then they are definitely alive).
		else if (stillAlive)
		{
			// If the player has taken the maximum number of steps and is not with Nero (i.e. they have not won
			// the game in the last turn allowed), set gameOver to true and print
			// a corresponding message
			if (stepsTaken == MAX_STEPS)
			{
				std::cout << "You have reached the maximum number of steps, and you are not with Nero.\n"; 
				std::cout << "We are now going to bring you back to the present since we don’t want you alone\n";
				std::cout << "in the city of Rome without the emperor’s protection at night.\n";
				
				gameOver = true;
				pressEnter();
			}
			
			// Otherwise, if the user has not reached the maximum number of steps,
			// call the move function so they can move to a new space.
			else
			{
				// clear screen and print same info as at beginning of turn before having player move
				
				std::system("clear");
				std::cout << "\tSteps Taken: " << stepsTaken << " of " << MAX_STEPS;
				std::cout << "\tCoins: " << money;
				std::cout << "\tCurrent Space: " << currentSpace->get_name() << std::endl << std::endl;
				print_satchel_contents();
				gameBoard.print_board();
				
				// Call the board's move function, and increment the number of steps taken
				gameBoard.move();
				stepsTaken++;
				
				// If the player has bathed, increment the stepsSinceBathing variable
				if (hasBathed)
				{
					stepsSinceBathing++;
				}
			}
		}
		
		// Otherwise, if the player has died, set gameOver to true.
		// No message is printed here since a specific message was already
		// printed in the interact function in which the player died.
		else
		{
			gameOver = true;
		}
	}

	// Otherwise, if the player has chosen to keep moving rather than enter and interact with the space,
	// check to see if this is the last turn allowed. If it is, print a message
	// and end the game. If it is not, allow them to move to a new space.
	else if (enterChoice == 2)
	{
		// If the player has taken the maximum number of steps and is not with Nero (i.e. they have not won
		// the game in the last turn allowed), set gameOver to true and print
		// a corresponding message
		if (stepsTaken == MAX_STEPS)
		{
			std::cout << "You have reached the maximum number of steps, and you are not with Nero.\n"; 
			std::cout << "We are now going to bring you back to the present since we don’t want you alone\n";
			std::cout << "in the city of Rome without the emperor’s protection at night.\n";
				
			gameOver = true;
			pressEnter();
		}
			
		// Otherwise, if the user has not reached the maximum number of steps,
		// call the move function so they can move to a new space.
		else
		{
			// clear screen and print same info as at beginning of turn before having player move
				
			std::system("clear");
			std::cout << "\tSteps Taken: " << stepsTaken << " of " << MAX_STEPS;
			std::cout << "\tCoins: " << money;
			std::cout << "\tCurrent Space: " << currentSpace->get_name() << std::endl << std::endl;
			print_satchel_contents();
			gameBoard.print_board();
				
			// Call the board's move function, and increment the number of steps taken
			gameBoard.move();
			stepsTaken++;
				
			// If the player has bathed, increment the stepsSinceBathing variable
			if (hasBathed)
			{
				stepsSinceBathing++;
			}
		}
	}
}


/*************************************************************************************************** 
 * Description: Private member function that prints the contents of the player's satchel.
 * 		Receives and returns nothing.
 ****************************************************************************************************/

void Game::print_satchel_contents()
{
	// If the satchel is empty, inform the user
	if (satchel.empty())
	{
		std::cout << "Your satchel is currently empty";
	}

	// Otherwise, print the current contents of the satchel
	else
	{
		std::set<std::string>::iterator iter;
		std::cout << "Satchel Contents: ";
		for (iter = satchel.begin(); iter != satchel.end(); iter++)
		{
			// Print the name of the item to which the iterator points
			std::cout << *iter;
			
			// Print a comma after the item name if it is not the last item in the satchel.
			// Test to see if this is the last element by incrementing iter,
			// seeing if it equals satchel.end(), and then decrementing it to get it back to current value.
			iter++;
			if (iter != satchel.end())
			{
				std::cout << ", ";
			}
			iter--;
		}
	}
}


/*************************************************************************************************** 
 * Description: Private member function called when the player has been received by Nero. Prints
 * 		a series of messages and text-based images as the ending to the game.
 * 		Receives and returns nothing.
 ****************************************************************************************************/

void Game::ending_sequence()
{
	std::system("clear");

	// Read in the ending sequence from text file
	std::ifstream inputFile("Ending_Sequence.txt");
	std::string text;
	
	while (getline(inputFile, text, DELIM))
	{
		std::cout << text;
	}
	
	// Close the input file and set gameOver to true
	inputFile.close();
	gameOver = true;
	
	pressEnter();
	std::cout << "Congratulations, time traveler! You win!\n";
	std::cout << "Thank you for your hard work in getting us this muusical score and recording from Rome!\n";
	pressEnter();
}


/***************************************************************************************************** 
 * Description: Accessor method that receives nothing and returns a bool indicating whether or not
 * 		the game is over.
 ****************************************************************************************************/

bool Game::game_over() const
{
	return this->gameOver;
}
