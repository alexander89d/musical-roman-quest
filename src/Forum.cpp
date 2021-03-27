/*************************************************************************************************** 
 * Program Name: Forum.cpp
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
#include "Forum.hpp"

/*************************************************************************************************** 
 * Description: Default constructor for Forum object.
 *
 * 		Calls Space constructor and passes it a string indicating a space's name, 
 * 		an int indicating its number on the map, and a string with the name of a 
 * 		.txt file containing its description. 
 * 		Space constructor then sets the name and num to the parameters received.
 * 		Opens input file and reads description into description data member.
 * 		Sets all space pointers to nullptr since the mutator methods will
 * 		later be used to set those pointers once all spaces have been created.
 *
 * 		Forum constructor also initializes private data members (vectors),
 * 		calling private make_purchase_menu() function for
 * 		assistance with making the menu.
 ***************************************************************************************************/

Forum::Forum() : Space("Forum", 5, "Forum_Description.txt")
{
	// Initialize 6 different items for purchase
	Item good1(OLIVE_OIL, EXPENSIVE_PRICE);
	Item good2(SANDALS, EXPENSIVE_PRICE);
	Item good3(WINE, EXPENSIVE_PRICE);
	Item good4(GRAIN, CHEAP_PRICE);
	Item good5(SALT, CHEAP_PRICE);
	Item good6(TUNIC, CHEAP_PRICE);
	
	// Add items to goodsForSale vector
	goodsForSale.push_back(good1);
	goodsForSale.push_back(good2);
	goodsForSale.push_back(good3);
	goodsForSale.push_back(good4);
	goodsForSale.push_back(good5);
	goodsForSale.push_back(good6);

	// Call private function to initialize purchaseMenu
	make_purchase_menu();
}


/*************************************************************************************************** 
 * Description: Private member function called by Forum constructor to initialize purchaseMenu
 * 		vector based on values stored in goodsForSale vector. Receives and returns nothing.
 ***************************************************************************************************/

void Forum::make_purchase_menu()
{
	// Iterate through the goodsForSale vector,
	// making a menu choice for each good listing both its name and price
	for (int index = 0; index < 6; index++)
	{
		// Get the item's name
		std::string menuChoice = goodsForSale[index].itemName;
		
		// Add the item's price (converted from int to string) to its menu choice
		menuChoice += " (" + std::to_string(goodsForSale[index].price) + " coins)";
		purchaseMenu.push_back(menuChoice);
	}
	
	// Add a "Leave the Forum" menu option for when user is done shopping or browsing
	purchaseMenu.push_back("Leave the Forum");
}


/*************************************************************************************************** 
 * Description: Virtual destructor for Forum class. Body of destructor
 * 		is empty since dynamically-allocated memory for each space will be created and
 * 		destroyed by the Board class. Nonetheless, the Space parent class
 * 		and its child classes include virtual destructors so that
 * 		their destructors are called in the proper order when they
 * 		are deleted.
 ***************************************************************************************************/

Forum::~Forum()
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
 *		# - a set of strings indicating the items in the player's satchel #
 *		# - an int indicating how much money the player has #
 *		  - an int indicating how many steps the player has taken since bathing 
 *		  - a bool indicating whether or not the player has bathed 
 *		  - a bool indicating whether or not the player knows about the scroll that
 *		    the librarian wants to be returned 
 *		  - a bool indicating whether or not the player is still alive
 *		  - a bool indicating whether or not the player is with Nero 
 *
 *		The Forum's implementation of this function does the following:
 *		- Allows the user to purchase items if they have enough money
 *		  to purchase a given item, their satchel has space, and they
 *		  do not already have that item.
 *		- User can buy multiple items in one stop. They must choose to exit the Forum.
 ***************************************************************************************************/

void Forum::interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
			   bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero)
{	
	int purchaseChoiceNum = 0;
	do
 	{
		// Ask the user what they would like to buy
		std::cout << "What would you like to buy?\n";
		purchaseChoiceNum = menu(purchaseMenu);
 		
		// If the user has not chosen to exit, process their purchase choice
		if (purchaseChoiceNum != 7)
		{
			// Determine the index of the item in the goodsForSale vector
			int itemNum = (purchaseChoiceNum-1);
			
			// Determine the name and cost of the item
			std::string itemName = goodsForSale[itemNum].itemName;
			int price = goodsForSale[itemNum].price;
 			
			// If the user's satchel has reached max capacity, inform them
			if (satchel.size() == SATCHEL_CAPACITY)
			{
				std::cout << "I’m sorry, but your satchel is at max capacity.\n";
				std::cout << "Please go to the theater. They are taking collections for a local orphanage\n";
				std::cout << "Once you have freed up room in your satchel, please come back here.\n";
			}
			
			// Otherwise, if the user already has the requested item, inform them that they cannot buy the item
			// again until they have gotten rid of the first of that item.
			else if (satchel.find(itemName) != satchel.end())
			{
				std::cout << "You already have this item. Please come back when you need more of this item,\n"; 
				std::cout << "or choose a different item.\n";
			}

			// Otherwise, if the user does not have enough money to purchase they item,
			// inform them.
			else if (money < price)
			{
				std::cout << "You do not have enough money to purchase this item.\n";
				std::cout << "Please choose a different item or come back later.\n";
			}
			
			// Otherwise, the user can purchase the item. Add the item to their satchel
			// and deduct its cost from their money.
			else
			{
				std::cout << "Here is your " << itemName << "!\n";
				satchel.insert(itemName);
				money -= price;
			}
		} 
		std::cout << std::endl;
	} while (purchaseChoiceNum != 7);
	
	std::cout << "Have a great day!\n";
	pressEnter();
}
