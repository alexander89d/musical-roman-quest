/*************************************************************************************************** 
 * Program Name: Space.cpp
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
#include "Space.hpp"


/*************************************************************************************************** 
 * Description: Constructor that receives a string indicating a space's name, an int indicating its
 * 		number on the map, and a string with the name of a .txt file containing its
 * 		description. Sets the name and num to the parameters received.
 * 		Opens input file and reads description into description data member.
 * 		Sets all space pointers to nullptr since the mutator methods will
 * 		later be used to set those pointers once all spaces have been created.
 * 		Constructor is called by child class constructors.
 * 		No default constructor is included since all child class constructors
 * 		will pass the required parameters to this parent class constructor
 * 		and no abstract Space objects can be instantiated.
 ***************************************************************************************************/

Space::Space(std::string name, int num, std::string inputFileName)
{
	// Set all space pointers to nullptr.
	this->north = nullptr;
	this->northeast = nullptr;
	this->east = nullptr;
	this->southeast = nullptr;
	this->south = nullptr;
	this->southwest = nullptr;
	this->west = nullptr;
	this->northwest = nullptr;
	
	// Set name and num based on parameters received.
	this->name = name;
	this->num = num;
	
	// Load space description from file. Description is one "line" of text
	// (even though there are newline characters throughout the description
	// for formatting purposes, there is a single delimination character
	// at the very bottom of the file so the entire description is read in at once).
	std::ifstream inputFile(inputFileName);
	getline(inputFile, description, DELIM);
	inputFile.close();
}


/*************************************************************************************************** 
 * Description: Virtual destructor for space class. Body of destructor
 * 		is empty since dynamically-allocated memory for each space will be created and
 * 		destroyed by the Board class. Nonetheless, this parent class
 * 		and its child classes include virtual destructors so that
 * 		their destructors are called in the proper order when they
 * 		are deleted.
 ***************************************************************************************************/

Space::~Space()
{
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameter and returns a space's name.
 ***************************************************************************************************/

std::string Space::get_name() const
{
	return this->name;
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameter and returns a space's number.
 ***************************************************************************************************/

int Space::get_num() const
{
	return this->num;
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameter and returns a space's description.
 ***************************************************************************************************/

std::string Space::get_description() const
{
	return this->description;
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameter and returns a pointer to the space
 * 		to the north.
 ***************************************************************************************************/

Space* Space::get_north() const
{
	return this->north;
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameter and returns a pointer to the space
 * 		to the northeast.
 ***************************************************************************************************/

Space* Space::get_northeast() const
{
	return this->northeast;
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameter and returns a pointer to the space
 * 		to the east.
 ***************************************************************************************************/

Space* Space::get_east() const
{
	return this->east;
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameter and returns a pointer to the space
 * 		to the southeast.
 ***************************************************************************************************/

Space* Space::get_southeast() const
{
	return this->southeast;
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameter and returns a pointer to the space
 * 		to the south.
 ***************************************************************************************************/

Space* Space::get_south() const
{
	return this->south;
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameter and returns a pointer to the space
 * 		to the southwest.
 ***************************************************************************************************/

Space* Space::get_southwest() const
{
	return this->southwest;
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameter and returns a pointer to the space
 * 		to the west.
 ***************************************************************************************************/

Space* Space::get_west() const
{
	return this->west;
}


/*************************************************************************************************** 
 * Description: Accessor method that receives no parameter and returns a pointer to the space
 * 		to the northwest.
 ***************************************************************************************************/

Space* Space::get_northwest() const
{
	return this->northwest;
}


/*************************************************************************************************** 
 * Description: Mutator method that sets a Space's north pointer to the pointer received as a
 * 		parameter. Returns nothing.
 ***************************************************************************************************/

void Space::set_north(Space* spacePtr)
{
	this->north = spacePtr;
}


/*************************************************************************************************** 
 * Description: Mutator method that sets a Space's northeast pointer to the pointer received as a
 * 		parameter. Returns nothing.
 ***************************************************************************************************/

void Space::set_northeast(Space* spacePtr)
{
	this->northeast = spacePtr;
}


/*************************************************************************************************** 
 * Description: Mutator method that sets a Space's east pointer to the pointer received as a
 * 		parameter. Returns nothing.
 ***************************************************************************************************/

void Space::set_east(Space* spacePtr)
{
	this->east = spacePtr;
}


/*************************************************************************************************** 
 * Description: Mutator method that sets a Space's southeast pointer to the pointer received as a
 * 		parameter. Returns nothing.
 ***************************************************************************************************/

void Space::set_southeast(Space* spacePtr)
{
	this->southeast = spacePtr;
}


/*************************************************************************************************** 
 * Description: Mutator method that sets a Space's south pointer to the pointer received as a
 * 		parameter. Returns nothing.
 ***************************************************************************************************/

void Space::set_south(Space* spacePtr)
{
	this->south = spacePtr;
}


/*************************************************************************************************** 
 * Description: Mutator method that sets a Space's southwest pointer to the pointer received as a
 * 		parameter. Returns nothing.
 ***************************************************************************************************/

void Space::set_southwest(Space* spacePtr)
{
	this->southwest = spacePtr;
}


/*************************************************************************************************** 
 * Description: Mutator method that sets a Space's west pointer to the pointer received as a
 * 		parameter. Returns nothing.
 ***************************************************************************************************/

void Space::set_west(Space* spacePtr)
{
	this->west = spacePtr;
}


/*************************************************************************************************** 
 * Description: Mutator method that sets a Space's northwest pointer to the pointer received as a
 * 		parameter. Returns nothing.
 ***************************************************************************************************/

void Space::set_northwest(Space* spacePtr)
{
	this->northwest = spacePtr;
}
