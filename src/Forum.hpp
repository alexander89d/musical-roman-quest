/*************************************************************************************************** 
 * Program Name: Forum.hpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: Forum class that is a child of the abstract Space class. Implements the
 * 		Forum (Market). In the Forum, the user can buy various items.
 * 		The user must buy 2 specific items randomly selected
 * 		by the soldier in the Campus Martius (one exensive item and one cheap item).
 *
 * 		Protected data members inherited by Space child classes include the following:
 * 		- Pointers to the Spaces in all 8 directions (north, northeast, east, etc.)
 * 		- A string representing the name of the space
 *		- An int representing the space's number (for use when displaying map of player's
 *		current location)
 *		- A string description of the space
 *		
 *		Item struct is declared as a private member of Forum class.
 *		The Item struct keeps track of the name and price of each item.
 *
 *		Private data members include the following:
 *		- A vector of items that contains all goods for sale
 *		- A vector of strings passed as an argument to the menu function 
 *		  to create a purchase menu
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
 *		In addition, this class has a private member function
 *		called by the constructor to intialize the purchase menu.
 **************************************************************************************************/
#ifndef FORUM_HPP
#define FORUM_HPP

#include "Space.hpp"

// Constants used by the Forum class to indicate prices of items
const int EXPENSIVE_PRICE = 14;
const int CHEAP_PRICE = 8;

class Forum : public Space
{
	private:
		// Struct that is private member of Forum class
		struct Item
		{	
			// Data members of struct include string for item's name and
			// int for item's price
			std::string itemName;
			int price;

			// Constructor initializes data members of item
			// to values of received parameters
			Item(std::string itemName, int price)
			{	
				this->itemName = itemName;
				this->price = price;
			}
		};
		
		// private data members
		std::vector<Item> goodsForSale;
		std::vector<std::string> purchaseMenu;

		// private member function
		void make_purchase_menu();

	public:
		// Public member functions
		Forum();
		virtual ~Forum();
		virtual void interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
				      bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero) override;
};
#endif
