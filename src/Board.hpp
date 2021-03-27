/*************************************************************************************************** 
 * Program Name: Board.hpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: Class that implements a Board object consisting of linked Space objects for use in 
 * 		the Ancient Rome-Themed game.
 *
 * 		An enum class included in the Board class's header file
 * 		defines the Direction data type for use in the Board class.
 *
 * 		Private data members of the Board class include the following:
 * 		- A vector containing text-based board images
 * 		- Pointers to each of the 9 different Spaces on the board
 * 		- A pointer to the space at which the player is currently located
 *
 *		Public member functions include:
 *		- A constructor and destructor
 *		- An accessor method that returns the Space pointer to the player's location
 *		- A function that prints an image of the board (including the player's location)
 *		- A function that moves the player on the board
 *
 *		Private member functions include:
 *		- A function that sets the choices of the menu of where the player can move
 *		  (based on which spaces, if any, are in each direction from the player)
 *		- A function that determines whether a move in a given direction is possible
 ***************************************************************************************************/
#ifndef BOARD_HPP
#define BOARD_HPP

// Include header files for 9 different space types
#include "Bibliotheca.hpp"
#include "DomusAurea.hpp"
#include "Ludus.hpp"
#include "CircusMaximus.hpp"
#include "Forum.hpp"
#include "Theatrum.hpp"
#include "Colosseum.hpp"
#include "Thermae.hpp"
#include "CampusMartius.hpp"

// Constant indicating the number of board images to be stored in boardImages data member
// (one image for each space on the board)
const int NUM_BOARD_IMAGES = 9;

// Enum class that defines Direction data type for use in Board class
enum class Direction{N, NE, E, SE, S, SW, W, NW};

// Board class declaration
class Board
{
	private:
		// Private data members
		std::vector<std::string> boardImages;
		Space* space1;
		Space* space2;
		Space* space3;
		Space* space4;
		Space* space5;
		Space* space6;
		Space* space7;
		Space* space8;
		Space* space9;
		Space* playerLocation;

		// Private member functions
		void set_move_menu(std::vector<std::string>& moveMenuChoices);
		bool is_valid_move(Direction dir);

	public:
		// Public member functions
		Board();
		~Board();
		Space* get_player_location() const;
		void print_board();
		void move();
};
#endif
