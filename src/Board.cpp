/*************************************************************************************************** 
 * Program Name: Board.cpp
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
#include "Board.hpp"


/*************************************************************************************************** 
 * Description: Default constructor of Board class. 
 *
 * 		Dynamically allocates memory for each space on the board (each of the 9 spaces
 * 		is a different type of space, represented by a different subclass of Space).
 *
 *		Assigns the space5 pointer to the player's starting
 *		location pointer (the player starts in the Forum).
 *
 *		Sets values of each Space's pointers to other Spaces
 *		(setting values only for directions in which there is another space and 
 *		leaving all other pointers at default value of nullptr).
 *
 *		Loads text-based images of Board from file into vector of strings.
 ***************************************************************************************************/

Board::Board()
{
	// Dynamically allocate memory for each of 9 Spaces
	// (each space pointer's number corresponds to that same number on the Board map).
	space1 = new Bibliotheca;
	space2 = new DomusAurea;
	space3 = new Ludus;
	space4 = new CircusMaximus;
	space5 = new Forum;
	space6 = new Theatrum;
	space7 = new Colosseum;
	space8 = new Thermae;
	space9 = new CampusMartius;

	// Set the player's starting location to space5 (the Forum)
	playerLocation = space5;

	// Set each space’s directional pointers (if a space does not have another space in a 
	// given direction, that direction’s pointer will be left as the default value of nullptr).
	
	// Set space1 pointers
	space1->set_east(space2);
	space1->set_southeast(space5);
	space1->set_south(space4);
	
	// Set space2 pointers
	space2->set_east(space3);
	space2->set_southeast(space6);
	space2->set_south(space5);
	space2->set_southwest(space4);
	space2->set_west(space1);

	// Set space3 pointers
	space3->set_south(space6);
	space3->set_southwest(space5);
	space3->set_west(space2);

	// Set space4 pointers
	space4->set_north(space1);
	space4->set_northeast(space2);
	space4->set_east(space5);
	space4->set_southeast(space8);
	space4->set_south(space7);

	// Set space5 pointers
	space5->set_north(space2);
	space5->set_northeast(space3);
	space5->set_east(space6);
	space5->set_southeast(space9);
	space5->set_south(space8);
	space5->set_southwest(space7);
	space5->set_west(space4);
	space5->set_northwest(space1);

	// Set space6 pointers
	space6->set_north(space3);
	space6->set_south(space9);
	space6->set_southwest(space8);
	space6->set_west(space5);
	space6->set_northwest(space2);

	// Set space7 pointers
	space7->set_north(space4);
	space7->set_northeast(space5);
	space7->set_east(space8);

	// Set space8 pointers
	space8->set_north(space5);
	space8->set_northeast(space6);
	space8->set_east(space9);
	space8->set_west(space7);
	space8->set_northwest(space4);

	// Set space9 pointers
	space9->set_north(space6);
	space9->set_west(space8);
	space9->set_northwest(space5);

	// Fill boardImages vector with strings of boardImages
	// by reading in from input file
	std::ifstream inputFile("Board_Images.txt");
	std::string image;

	// Use a for loop to read in each image from the file
	// The images are each multiple lines, so they are
	// separated by the delimination character '#'
	for(int index = 0; index < NUM_BOARD_IMAGES; index++)
	{
		getline(inputFile, image, DELIM);
		boardImages.push_back(image);	
	}
	inputFile.close();
}


/*************************************************************************************************** 
 * Description: Destructor that deallocates memory dynamically allocated for each space.
 ***************************************************************************************************/

Board::~Board()
{
	delete space1;
	space1 = nullptr;
	delete space2;
	space2 = nullptr;
	delete space3;
	space3 = nullptr;
	delete space4;
	space4 = nullptr;
	delete space5;
	space5 = nullptr;
	delete space6;
	space6 = nullptr;
	delete space7;
	space7 = nullptr;
	delete space8;
	space8 = nullptr;
	delete space9;
	space9 = nullptr;
	playerLocation = nullptr;
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameters and returns the Space pointer indicating
 * 		the space at which the player is located.
 ***************************************************************************************************/

Space* Board::get_player_location() const
{
	return this->playerLocation;
}


/*************************************************************************************************** 
 * Description: Function that prints an image of the board when called based on the player's current
 * 		location (the square in which the player is located is marked with an
 * 		asterisk centered in the bottom row). Receives and returns nothing.
 ***************************************************************************************************/

void Board::print_board()
{
	// Determine which board to print based on the number of the space
	// at which the player is located (Spaces are numbered 1-9;
	// subtracting 1 from player's space num gives the index in the images
	// vector corresponding to the player's current location).
	int boardIndex = (playerLocation->get_num() -1);
	std::cout << boardImages[boardIndex];
}


/*************************************************************************************************** 
 * Description: Function that moves the player from one space to another
 * 		(assigns a different space's pointer to the playerLocation pointer).
 *		Lists choices of all possible spaces to which the player can move
 *		(lists all 8 directions but indicates those in which the
 *		user cannot move and the names of the spaces in each direction that the player can 
 *		move). Validates the user's choice, only allowing them to move
 *		in a valid direction. Receives and returns nothing.
 ***************************************************************************************************/

void Board::move()
{
	// Declare a vector to store the move menu choices.
	std::vector<std::string> moveChoices;

	// Pass the vector to set_move_menu private function so that
	// it can be initialized with menu choices based on the player's current location
	set_move_menu(moveChoices);

	// Ask the user in what direction they would like to move
	std::cout << "In what direction would you like to move?\n";

	// declare variables for use in do-while loop
	bool validMove = false;
	Direction dir;
	
	// Loop to receive user's choice; repeat until user
	// chooses a valid direction in which to move.
	do
	{
		// Get the user's choice for direction in which to move.
		int moveChoiceNum = menu(moveChoices);
		
		// Decrement the choice number so that it corresponds to
		// the correct enum value, and static cast it to a Direction
		moveChoiceNum--;	
		dir = static_cast<Direction>(moveChoiceNum);

		// Check whether a move in the direction the user selected is valid.
		// If it is not, prompt them to enter a new choice before looping again.
		validMove = is_valid_move(dir);
		if (!validMove)
		{
			std::cout << "You cannot move in that direction; please pick a different direction.\n";
		}
	} while (!validMove);
	
	// Now that the move choice has been validated, move the player to the new space based on the validated
	// direction.
	if (dir == Direction::N)
	{
		playerLocation = playerLocation->get_north();
	}
	else if (dir == Direction::NE)
	{
		playerLocation = playerLocation->get_northeast();
	}
	else if (dir == Direction::E)
	{
		playerLocation = playerLocation->get_east();
	}
	else if (dir == Direction::SE)
	{
		playerLocation = playerLocation->get_southeast();
	}
	else if (dir == Direction::S)
	{
		playerLocation = playerLocation->get_south();
	}
	else if (dir == Direction::SW)
	{
		playerLocation = playerLocation->get_southwest();
	}
	else if (dir == Direction::W)
	{
		playerLocation = playerLocation->get_west();
	}
	else if (dir == Direction::NW)
	{
		playerLocation = playerLocation->get_northwest();
	}
}


/*************************************************************************************************** 
 * Description: Private member function that receives empty string vector passed
 * 		by reference that it fills with the move menu choices based
 * 		on the player's current location. Returns nothing.
 ***************************************************************************************************/

void Board::set_move_menu(std::vector<std::string>& moveChoices)
{
	// For the sake of consistency with what each direction’s number is in the menu, all 
	// directions will be printed as choices, even if they player cannot move in that direction. 
	// After the name of the direction, the name of the space that is in that direction will be
	// printed or the message “cannot move in this direction” will be printed if applicable.
 	
	// Declare string with message about not being able to move in a given direction
	// (added to the end of a direction's menu option when applicable).
	std::string cannotMove = "(cannot move in this direction)";
 	
	// Make a menu option for each direction.
	// Check to see if the user can move in that direction, adding the name
	// of the space if the user can move in that direction
	// or the cannotMove message if they cannot move in that direction.
	std::string directionMenuOption = "North: ";
 	if (playerLocation->get_north() != nullptr)
 	{
		directionMenuOption += playerLocation->get_north()->get_name();
 	}
	else
 	{
		directionMenuOption += cannotMove;
 	}
 	moveChoices.push_back(directionMenuOption);
 	
	directionMenuOption = "Northeast: ";
	if (playerLocation->get_northeast() != nullptr)
 	{
		directionMenuOption += playerLocation->get_northeast()->get_name();
 	}
	else
 	{
		directionMenuOption += cannotMove;
 	}
 	moveChoices.push_back(directionMenuOption);
	
	directionMenuOption = "East: ";
	if (playerLocation->get_east() != nullptr)
 	{
		directionMenuOption += playerLocation->get_east()->get_name();
 	}
	else
 	{
		directionMenuOption += cannotMove;
 	}
 	moveChoices.push_back(directionMenuOption);

	directionMenuOption = "Southeast: ";
	if (playerLocation->get_southeast() != nullptr)
 	{
		directionMenuOption += playerLocation->get_southeast()->get_name();
 	}
	else
 	{
		directionMenuOption += cannotMove;
 	}
 	moveChoices.push_back(directionMenuOption);

	directionMenuOption = "South: ";
	if (playerLocation->get_south() != nullptr)
 	{
		directionMenuOption += playerLocation->get_south()->get_name();
 	}
	else
 	{
		directionMenuOption += cannotMove;
 	}
 	moveChoices.push_back(directionMenuOption);

	directionMenuOption = "Southwest: ";
	if (playerLocation->get_southwest() != nullptr)
 	{
		directionMenuOption += playerLocation->get_southwest()->get_name();
 	}
	else
 	{
		directionMenuOption += cannotMove;
 	}
 	moveChoices.push_back(directionMenuOption);

	directionMenuOption = "West: ";
	if (playerLocation->get_west() != nullptr)
 	{
		directionMenuOption += playerLocation->get_west()->get_name();
 	}
	else
 	{
		directionMenuOption += cannotMove;
 	}
 	moveChoices.push_back(directionMenuOption);

	directionMenuOption = "Northwest: ";
	if (playerLocation->get_northwest() != nullptr)
 	{
		directionMenuOption += playerLocation->get_northwest()->get_name();
 	}
	else
 	{
		directionMenuOption += cannotMove;
 	}
 	moveChoices.push_back(directionMenuOption);
}


/****************************************************************************************************
 * Description: Private member function that receives the direction that the user has
 * 		requested to move. Returns a boolean value indicating
 * 		whether or not the user can move in that direction.
 ***************************************************************************************************/

bool Board::is_valid_move(Direction dir)
{
	// Use nested conditionals to test whether
	// the user can move in the specified direction.
	// Return false if the pointer to that direction is nullptr,
	// true if it is a valid space.
	if (dir == Direction::N)
	{
		if (playerLocation->get_north() == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	else if (dir == Direction::NE)
	{
		if (playerLocation->get_northeast() == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	else if (dir == Direction::E)
	{
		if (playerLocation->get_east() == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	else if (dir == Direction::SE)
	{
		if (playerLocation->get_southeast() == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	else if (dir == Direction::S)
	{
		if (playerLocation->get_south() == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	else if (dir == Direction::SW)
	{
		if (playerLocation->get_southwest() == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	else if (dir == Direction::W)
	{
		if (playerLocation->get_west() == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	else if (dir == Direction::NW)
	{
		if (playerLocation->get_northwest() == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
