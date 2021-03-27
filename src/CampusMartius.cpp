/*************************************************************************************************** 
 * Program Name: CampusMartius.cpp
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
#include "CampusMartius.hpp"

/*************************************************************************************************** 
 * Description: Default constructor for DomusAurea object.
 *
 * 		Calls Space constructor and passes it a string indicating a space's name, 
 * 		an int indicating its number on the map, and a string with the name of a 
 * 		.txt file containing its description. 
 * 		Space constructor then sets the name and num to the parameters received.
 * 		Opens input file and reads description into description data member.
 * 		Sets all space pointers to nullptr since the mutator methods will
 * 		later be used to set those pointers once all spaces have been created.
 *
 * 		Also initializes private data members of CampusMartius class,
 *		randomly selecting which expensive item and which cheap item
 *		the prefect desires in the process.
 ***************************************************************************************************/

CampusMartius::CampusMartius() : Space("Campus Martius", 9, "CampusMartius_Description.txt")
{
	// Initialize all bool data members to false
	hasPassedTest = false;
	hasGivenExpensive = false;
	hasGivenCheap = false;

	// Fill vectors with the names of the expensive
	// and cheap items, and randomly select an item
	// from each vector
	std::vector<std::string> expensiveItems = {OLIVE_OIL, SANDALS, WINE};
	std::vector<std::string> cheapItems = {GRAIN, SALT, TUNIC};
	expensiveChoice = expensiveItems[getRandomInt(0, 2)];
	cheapChoice = cheapItems[getRandomInt(0, 2)];
}


/*************************************************************************************************** 
 * Description: Virtual destructor for CampusMartius class. Body of destructor
 * 		is empty since dynamically-allocated memory for each space will be created and
 * 		destroyed by the Board class. Nonetheless, the Space parent class
 * 		and its child classes include virtual destructors so that
 * 		their destructors are called in the proper order when they
 * 		are deleted.
 ***************************************************************************************************/

CampusMartius::~CampusMartius()
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
 *		  - an int indicating how much money the player has 
 *		  - an int indicating how many steps the player has taken since bathing 
 *		  - a bool indicating whether or not the player has bathed 
 *		  - a bool indicating whether or not the player knows about the scroll that
 *		    the librarian wants to be returned 
 *		# - a bool indicating whether or not the player is still alive #
 *		  - a bool indicating whether or not the player is with Nero
 *
 *		The CampusMartius's implementation of this function does the following:
 *		- Allows the player to interact with the Praetorian Prefect (leader of bodyguards)
 *		  to prove trustworthiness to Prefect.
 *		- If the user proves trustworthiness, they must then
 *		  obtain one cheap and one expensive item from the forum
 *		  randomly selected by the Prefect.
 *		- Once they bring back these items, the user receives the permit
 *		  to see Nero.
 ***************************************************************************************************/

void CampusMartius::interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
			   bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero)
{
	// If the user has not yet passed the prefect's trustworthiness test,
	// call the test_user function, storing the return value
	// in the stillAlive reference variable
	if (!hasPassedTest)
	{
		stillAlive = test_user();
	}
	
	// Otherwise, if the user has not yet obtained the permit,
	// call the give_items function to check whether or not
	// they have the requested items and remove them from the satchel
	// if they do. Note: If the user has obtained the permit,
	// they will possess it until the end of the game.
	// Therefore, simply check satchel for permit.
	else if(satchel.find(PERMIT) == satchel.end())
	{
		give_items(satchel);
	}
	
	// Otherwise, the prefect urges the user to hurry up and see Nero
	// now that they have the permit.
	else
	{
		std::cout << "I’ve already given you permission to see Nero.\n"; 
		std::cout << "What are you waiting for? Get to the Domus Aurea at once!\n";
	}
	pressEnter();
}


/*************************************************************************************************** 
 * Description: Private member function that executes the prefect's test of the user
 * 		in which he asks them 3 questions to test their loyalty. Receives no parameters.
 * 		Returns a bool indicating whether or not the user has passed the test.
 ***************************************************************************************************/

bool CampusMartius::test_user()
{
	// Prefect stops and interrogates player
	std::cout << "Halt! Who goes there?\n";
	std::cout << "You say you want to see Nero?\n";
	std::cout << "Well, I, Gaius Silius, am the Prefect of the Praetorian Guard.\n";
	std::cout << "Emperor Nero is very busy, so in order to see him, you’ll need my permission.\n";
	std::cout << "I will ask you 3 questions to see if you are worthy of seeing the emperor.\n\n";
	
	// Ask user first question. Return false if they answer incorrectly. Otherwise,
	// proceed to next question.
	std::cout << "Of what country are you a citizen?\n";
	std::vector<std::string> question1Choices = {"The United States", "Rome", "Germany"};
	int answerChoice = menu(question1Choices);
	
	if (answerChoice == 2)
	{
		std::cout << "OK, so you are a Roman. Good thing, because I do not trust non-Romans.\n";
	}
	else
	{
		std::cout << "I don’t trust non-Romans, especially those who want an audience with the emperor.\n";
		std::cout << "I must kill you now for the protection of the emperor.\n";
		return false;
	}
	
	// Ask user second question, returning false if they answer incorrectly and proceeding
	// to the final question if they answer correctly.
	std::cout << "\nWho is the best emperor?\n";
	std::vector<std::string> question2Choices = {"Nero", "Caligula", "Augustus"};
	answerChoice = menu(question2Choices);
	
	if (answerChoice == 1)
	{
		std::cout << "I agree! Nero is the best emperor! Long live Nero!\n";
	}
	else
	{
		std::cout << "This is treason! How dare you be such a traitor to your country?\n"; 
		std::cout << "Clearly, Nero is the best emperor ever. You must be plotting to overthrow him …\n"; 
		std::cout << "I know some scoundrles have talked of such plans, and I am to immediately\n"; 
		std::cout << "execute anyone on the spot who even hints at conspiracy.\n";
		std::cout << "Time to die, traitor!\n";
		return false;
	}
	
	// Ask user the final question. If they answer correctly, return true
	// and set hasPassedTest data member to true. Otherwise,
	// return false.
	std::cout << "\nWhat was Nero’s role in the Great Fire?\n";
	std::vector<std::string> question3Choices = {"He started it.", "He played the lyre while Rome burned.",
						    "He made improvements to Rome after the Great Fire to prevent future fires."};
	answerChoice = menu(question3Choices);
	
	if (answerChoice == 3)
	{
		std::cout << "I am glad you acknowledge just how much our great emperor has done\n";
		std::cout << "to protect Rome from future fires! I can’t believe those traitors\n";
		std::cout << "who claim he started the fire or played his lyre while Rome burned.\n\n";
		
		std::cout << "Clearly, you are a supporter of Nero who is worthy to see the emperor.\n";
		std::cout << "\nI do have a favor to ask before I give you permission to visit Nero, though.\n";
		std::cout << "Could you pick some items up for me in the Forum?\n";
		std::cout << "I am on duty the rest of the day but could use the following items:\n";
		std::cout << "\t- " << expensiveChoice << std::endl;
		std::cout << "\t- " << cheapChoice << std::endl;
		std::cout << "\nReturn here with those, and I will be happy to give you a permit to see Nero.\n";
		
		hasPassedTest = true;
		return true;
	}
	else
	{
		std::cout << "How dare you insult our dear emperor like that! All honest, trustworthy Roman citizens\n";
		std::cout << "know that Nero was deeply grieved by the Great Fire and did everything in his power\n"; 
		std::cout << "to prevent future fires.\n";
		std::cout << "You may have survived the Great Fire, but you will not survive my wrath.\n";
		std::cout << "For Nero!\n";
		return false;
	}
}


/*************************************************************************************************** 
 * Description: Private member function that allows user to give items
 * 		in their satchel to the prefect in order to obtain the permit
 * 		to see Nero. Receives the set of strings representing the items
 * 		in the user's satchel passed by reference. Returns nothing.
 ***************************************************************************************************/

void CampusMartius::give_items(std::set<std::string>& satchel)
{
	// Check to see if the user has already given each item.
	// For each item that the user has not given, check to see if it is available to give now
	// and remove it from stachel if present using check_for_item function.
	if (!hasGivenExpensive)
	{
		hasGivenExpensive = check_for_item(satchel, expensiveChoice);
	}
	if (!hasGivenCheap)
	{
		hasGivenCheap = check_for_item(satchel, cheapChoice);
	}

	// Now that the user has given each item if they have it,
	// print appropriate messages depending on what the soldier still needs
	
	// If the user has not given the prefect either item,
	// request that they return with both.
	if (hasGivenExpensive == false && hasGivenCheap == false)
	{
		std::cout << "I am still waiting on the " << expensiveChoice << " and " << cheapChoice << " from you.\n";
		std::cout << "Bring them to me as soon as you have them!\n";
	}

	// Otherwise, if the user has not given the expensive item (but has given the cheap one),
	// respond by requesting the expensive item.
	else if (!hasGivenExpensive)
	{
		std::cout << "Although you have brought me the " << cheapChoice << ",\n"; 
		std::cout << "I am still waiting on the " << expensiveChoice << " from you. Bring it to me right away!\n";
	}

	// Otherwise, if the user has not given the cheap item (but has given
	// the expensive item), request that they return with the cheap item
	else if (!hasGivenCheap)
	{
		std::cout << "Although you have brought me the " << expensiveChoice << ",\n";
		std::cout << "I am still waiting on the " << cheapChoice << " from you.\n"; 
		std::cout << "If you can afford to buy me the " << expensiveChoice << ",\n";
		std::cout << "you can afford to buy me the " << cheapChoice << "! Come back as soon as you have it!\n";
	}
	
	// Otherwise, since the user has given the soldier both items that
	// he has requested, he gives them the permit to see Nero.
	else
	{
		std::cout << "Since you have brought me the " << expensiveChoice << " and the " << cheapChoice; 
		std::cout << " like I asked,\nI will give you permission to see the Great Emperor Nero.\n";
		satchel.insert(PERMIT);
	}
}


/*************************************************************************************************** 
 * Description: Private member function called by give_items() function that checks to see whether
 * 		or not the user's satchel contains a given item. Receives the set of strings 
 * 		representing the contents of the player's satchel passed by reference
 * 		as well as a string representing the name of the item sought
 * 		passed by value. Removes the item from the player's satchel if found. 
 * 		Returns a bool indicating whether or not the item was found.
 ***************************************************************************************************/

bool CampusMartius::check_for_item(std::set<std::string>& satchel, std::string itemName)
{
	// First, check to see if the satchel is empty,
	// returning false if it is.
	if (satchel.empty())
	{
		return false;
	}
	
	// Otherwise, if the item is not in the satchel,
	// return false.
	else if (satchel.find(itemName) == satchel.end())
	{
		return false;
	}
	
	// Otherwise, since the item was founc,
	// remove the item from the use'rs satchel
	// and inform them that they have given it to the soldier.
	// Return true to indicate that the item was found.
	else
	{
		std::cout << "Now giving the soldier the " << itemName << "...\n";
		satchel.erase(itemName);

		pressEnter();

		return true;
	}
}
