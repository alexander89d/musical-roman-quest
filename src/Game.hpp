/*************************************************************************************************** 
 * Program Name: Game.hpp
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
#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"

// Constant indicating the maximum number of steps between spaces allowed in a game
const int MAX_STEPS = 75;

class Game
{
	private:
		// Private data members
		Board gameBoard;
		std::set<std::string> satchel;
		int money;
		int stepsTaken;
		int stepsSinceBathing;
		bool hasBathed;
		bool knowsAboutScroll;
		bool stillAlive;
		bool withNero;
		bool gameOver;
		
		// Private member functions
		void print_satchel_contents();
		void ending_sequence();

	public:
		// Public member functions
		Game();
		void take_turn();
		bool game_over() const;
};
#endif
