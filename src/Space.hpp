/*************************************************************************************************** 
 * Program Name: Space.hpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: Abstract class that creates an abstract Space object for use in Ancient Rome-themed
 * 		game. Each child class (representing a different type of space) has an interact
 * 		function that determines how the user interacts with that space (the interact
 * 		function is a pure virtual function in this parent class).
 *
 * 		Protected data members inherited by child classes include the following:
 * 		- Pointers to the Spaces in all 8 directions (north, northeast, east, etc.)
 * 		- A string representing the name of the space
 *		- An int representing the space's number (for use when displaying map of player's
 *		current location)
 *		- A string description of the space
 *
 *		Member functions of this class include:
 *		- A constructor and destructor
 *		- Accessor and mutator methods for all space pointers
 *		- Accessor methods for space name, number, and description
 *		- A pure virtual interact function defined in each child class
 **************************************************************************************************/
#ifndef SPACE_HPP
#define SPACE_HPP

#include <fstream>
#include <set>
#include "getRandomInt.hpp"
#include "pressEnter.hpp"
#include "menu.hpp"

// Global constants used by child classes and other program files as needed
// (all other program files either directly or indirectly include the Space class)

const char DELIM = '#';			// delimination character used with "getline" function for file input
const int SATCHEL_CAPACITY = 3;		// max number of items user can carry at one time
const std::string SCROLL = "scroll";	// The remaining string constants are used for satchel items (satchel is a string set)
const std::string PERMIT = "permit";
const std::string OLIVE_OIL = "olive oil";
const std::string SANDALS = "sandals";
const std::string WINE = "wine";
const std::string GRAIN = "grain";
const std::string SALT = "salt";
const std::string TUNIC = "tunic";

// Class declaration
class Space
{
	protected:
		Space* north;
		Space* northeast;
		Space* east;
		Space* southeast;
		Space* south;
		Space* southwest;
		Space* west;
		Space* northwest;
		std::string name;
		int num;
		std::string description;
	
	public:
		Space(std::string name, int num, std::string inputFileName);
		virtual ~Space();
		std::string get_name() const;
		int get_num() const;
		std::string get_description() const;
		Space* get_north() const;
		Space* get_northeast() const;
		Space* get_east() const;
		Space* get_southeast() const;
		Space* get_south() const;
		Space* get_southwest() const;
		Space* get_west() const;
		Space* get_northwest() const;
		void set_north(Space* spacePtr);
		void set_northeast(Space* spacePtr);
		void set_east(Space* spacePtr);
		void set_southeast(Space* spacePtr);
		void set_south(Space* spacePtr);
		void set_southwest(Space* spacePtr);
		void set_west(Space* spacePtr);
		void set_northwest(Space* spacePtr);
		
		// Pure virtual function defined in each child class
		// (see child class source files for description of each parameter as well as
		// which specific parameters each child class makes use of).
		virtual void interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
				      bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero) = 0;
};
#endif
