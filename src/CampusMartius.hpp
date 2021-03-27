/*************************************************************************************************** 
 * Program Name: CampusMartius.hpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: CampusMartius class that is a child of the abstract Space class. Implements the
 * 		CampusMartius (Military Training Field). At this space, the player
 * 		obtains the permit to see Nero from the Praetorian Prefect (leader of Nero's
 * 		bodyguards). The player must answer 3 questions that
 * 		the prefect asks correctly to gain the prefect's trust. Answering
 * 		any of them incorrectly results in the player's death and they
 * 		immediately lose the game. (The same 3 questions are asked by the 
 * 		prefect every game, so the player can make note of the correct answer to any 
 * 		they got wrong when playing again.) Once the player gains the prefect's
 * 		trust, he asks them to bring him 2 items from the Forum (1 expensive and 1 cheap).
 * 		The 2 particular items are randomly selected when the CampusMartius constructor is called.
 * 		Once the player delivers these items, they receive the permit
 * 		to see Nero.
 *
 * 		Protected data members inherited by Space child classes include the following:
 * 		- Pointers to the Spaces in all 8 directions (north, northeast, east, etc.)
 * 		- A string representing the name of the space
 *		- An int representing the space's number (for use when displaying map of player's
 *		current location)
 *		- A string description of the space
 *		
 *		Additional private data members of CampusMartius class include the following:		
 *		- A bool indicating whether or not the player has passed the prefect's trust test
 *		  (that way, when they revisit the space, they do not have to pass it again)
 *		- A string indicating the expensive item the prefect wants
 *		- A string indicating the cheap item the prefect wants
 *		- A bool indicating whether or not the prefect has already received
 *		  the expensive item from the user (so he does not ask for it again once given it).
 *		- A bool indicating whether or not the prefect has already
 *		  received the cheap item from the player (so he does not ask for it again).
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
 *		Private member functions of this class include:
 *		- A function called for the prefect to ask the 3 questions of the user
 *		- A function called for the player to give the prefect items
 *		- A function called to determine whether or not the player has certain items
 **************************************************************************************************/
#ifndef CAMPUSMARTIUS_HPP
#define CAMPUSMARTIUS_HPP

#include "Space.hpp"

class CampusMartius : public Space
{
	private:
		// Private data members
		bool hasPassedTest;
		std::string expensiveChoice;
		std::string cheapChoice;
		bool hasGivenExpensive;
		bool hasGivenCheap;
		
		// Private member functions
		bool test_user();
		void give_items(std::set<std::string>& satchel);
		bool check_for_item(std::set<std::string>& satchel, std::string itemName);
		
	public:
		// Public member functions
		CampusMartius();
		virtual ~CampusMartius();
		virtual void interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
				      bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero) override;
};
#endif
