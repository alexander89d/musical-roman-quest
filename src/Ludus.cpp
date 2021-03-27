/*************************************************************************************************** 
 * Program Name: Ludus.cpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: Ludus class that is a child of the abstract Space class. Implements the
 * 		Ludus (school). The player can visit this space to answer trivia questions for the
 * 		chance to win coins. If they visit the Bibliotheca and learn that the librarian
 * 		wants a scroll back from the teacher, they can obtain the scroll from this space.
 *
 * 		Protected data members inherited by Space child classes include the following:
 * 		- Pointers to the Spaces in all 8 directions (north, northeast, east, etc.)
 * 		- A string representing the name of the space
 *		- An int representing the space's number (for use when displaying map of player's
 *		current location)
 *		- A string description of the space
 *		
 *		The following struct is declared as a private member of the Ludus class:
 *		- Question (a struct containing the text of a trivia question,
 *		  the text of its answer choices, and an int representing the correct choice number).
 *
 *		In addition, the Ludus class contains the following private data members:
 *		- A vector of Question objects
 *		- A vector of strings representing students' names
 *		- A boolean indicating whether or not the player has already
 *		  obtained the scroll from the teacher (that way, once the player
 *		  gives the scroll back to the librarian, the teacher does not
 *		  erroneously try to give it to them again).
 *		- An int indicating the number of trivia games played
 *		- An int indicating how many trivia questions have been asked
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
 *		In addition, a private member function of the Ludus class simulates the playing
 *		of an individual trivia game.
 **************************************************************************************************/
#include "Ludus.hpp"

/*************************************************************************************************** 
 * Description: Default constructor for Ludus object.
 *
 * 		Calls Space constructor and passes it a string indicating a space's name, 
 * 		an int indicating its number on the map, and a string with the name of a 
 * 		.txt file containing its description. 
 * 		Space constructor then sets the name and num to the parameters received.
 * 		Opens input file and reads description into description data member.
 * 		Sets all space pointers to nullptr since the mutator methods will
 * 		later be used to set those pointers once all spaces have been created.
 *
 * 		In addition, the Ludus constructor
 * 		initializes all data members of the Ludus class.
 * 		It reads in the questions for the questions vector
 * 		from a text file. It then uses the "random shuffle" function
 * 		of the <algorithm> header file to shuffle order of the questions.
 ***************************************************************************************************/

Ludus::Ludus() : Space("Ludus", 3, "Ludus_Description.txt")
{
	// Read questions from file into vector
	std::ifstream inputFile("Ludus_Questions.txt");
	for (int questionNum = 0; questionNum < NUM_QUESTIONS; questionNum++)
	{
		Question q;
		std::string text;
		
		// Get question text
		getline(inputFile, text);
		q.questionText = text;
		
		// Get text of each answer choice
		for (int choiceNum = 0; choiceNum < NUM_CHOICES; choiceNum++)
		{
			getline(inputFile, text);
			q.answerChoices.push_back(text);
		}
		
		// Read in answer number as string and convert to int
		getline(inputFile, text);
		q.answerNum = stoi(text);
		
		// Add the intialized question to the questions vector
		questions.push_back(q);
	}
	
	// Close the input file and shuffle the questions
	inputFile.close();

	// Shuffle the questions a random number of times to make their order more truly random.
	int shuffleTimes = getRandomInt(1, 50);
	
	for (int count = 1; count <= shuffleTimes; count++)
	{
		random_shuffle(questions.begin(), questions.end());
	}
	
	// Fill the studentNames vector with 5 Greek/Roman names
	studentNames.push_back("Cornelius");
	studentNames.push_back("Marcus");
	studentNames.push_back("Julius");
	studentNames.push_back("Philemon");
	studentNames.push_back("Quintus");
	
	// Initialize the remaining data members
	obtainedScroll = false;
	gamesPlayed = 0;
	questionsAsked = 0;
}


/*************************************************************************************************** 
 * Description: Virtual destructor for Ludus class. Body of destructor
 * 		is empty since dynamically-allocated memory for each space will be created and
 * 		destroyed by the Board class. Nonetheless, the Space parent class
 * 		and its child classes include virtual destructors so that
 * 		their destructors are called in the proper order when they
 * 		are deleted.
 ***************************************************************************************************/

Ludus::~Ludus()
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
 *		# - a bool indicating whether or not the player knows about the scroll that
 *		    the librarian wants to be returned #
 *		  - a bool indicating whether or not the player is still alive
 *		  - a bool indicating whether or not the player is with Nero 
 *
 *		The Ludus's implementation of this function does the following:
 *		- Checks to see if the user knows about the scroll
 *		  which the librarian wants returned and gives the scroll to the user
 *		  if they have not been given it yet but know about it and have room in their satchel.
 *		- Allows the user to play up to 5 games of trivia 1-on-1 against one of the
 *		  schoolmaster's students. Trivia is free to play, and the
 *		  player wins coins by winning trivia. Uses private play_trivia
 *		  function to implement individual games of trivia.
 ***************************************************************************************************/

void Ludus::interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
			   bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero)
{
	std::cout << "Welcome to my school!\n";
	
	// Check to see if the player knows about the scroll. If so, the magister (teacher) tries to give it to them
	// if he has not done so already.
	if (obtainedScroll == false && knowsAboutScroll == true)
	{
		std::cout << "Thanks for offering to take the scroll back to the Bibliotheca\n"; 
		std::cout << "about which that grouchy librarian has been pestering me!\n";
	
		// Make sure satchel can hold the scroll. If it can, add the scroll to the user's satchel.
		if (satchel.size() < SATCHEL_CAPACITY)
		{
			std::cout << "Here's the scroll!\n";
			satchel.insert(SCROLL);
			obtainedScroll = true;
		}

		// Otherwise, prompt the user to come back when they
		// have room in their satchel for the scroll.
		else
		{
			std::cout << "I see you do not have room in your satchel for the scroll.\n";
			std::cout << "The theater is collecting unneeded items as donations for the poor.\n";
			std::cout << "I suggest you go there and then come back if you want that scroll.\n";
		}
		pressEnter();
	}
	
	// Next, if the user has not already played the max number of trivia games allowed,
	// ask if they want to play trivia.
	if (gamesPlayed < NUM_GAMES)
	{
		std::cout << "Would you like to prove your knowledge by playing trivia against one of my fine students?\n";
		std::vector<std::string> triviaMenu = {"Accept the challenge", "Decline the challenge"};
		int triviaChoice = menu(triviaMenu);
		
		// If the user has chosen to play trivia, call play_trivia function to run
		// a game of trivia. Add the return value of money
		// earned from that game to the player's current money.
		// (4 coins if player wins, 2 if ties, 0 if loses).
		if (triviaChoice == 1)
		{
			money += play_trivia();
		}
	}
	
	// Otherwise, if the user has already played the maximum number of rounds of trivia
	// allowed in a game, print a message saying that the students have gone home for the day.
	else
	{
		std::cout << "Since my students have gone home for the day, there is no more trivia to play.\n";
		std::cout << "Have a great day!\n";
		
		pressEnter();
	}
}


/*************************************************************************************************** 
 * Description: Private member function called from within interact function. Simulates
 * 		a game of trivia. Receives no parameters. Returns an int indicating how much money
 * 		the player has won (0 if nothing won).
 ***************************************************************************************************/

int Ludus::play_trivia()
{
	std::system("clear");

	// Print trivia rules
	std::cout << "Trivia Rules:\n\n";
	std::cout << "5 questions will be asked, and whoever gets the most right wins.\n";
	std::cout << "1 point will be awarded for correct answers. There is no penalty for incorrect answers.\n";
	std::cout << "If the game is tied after 5 questions, then tie-breaker questions will be asked\n"; 
	std::cout << "until a definitive winner is chosen or 5 tie-breaker questions have been asked (whichever occurs first).\n";
	std::cout << "\nPrizes:\n";
	std::cout << "\t- 4 coins for winning\n";
	std::cout << "\t- 2 coins for tying\n";
	std::cout << "\t- 0 coins for losing\n";

	pressEnter();

	// Declare local variables for use in trivia game.
	int userScore = 0;
	int computerScore = 0;
	int round = 1;

	// There are the same number of student names in the students vector
	// as their are games that can be played. Use the value of gamesPlayed
	// to determine the index of the student name to use for this game.
	std::string computerName = studentNames[gamesPlayed];
	
	// Ask 5 trivia questions
	for (round = 1; round <= 5; round++)
	{
		std::system("clear");

		// Print round information and current scores
		std::cout << "\t\tRound " << round << "\n\n";
		std::cout << "Scores:\n";
		std::cout << "\tYou: " << userScore << std::endl;
		std::cout << "\t" << computerName << " (student): " << computerScore << std::endl << std::endl;
		
		// Get the question at the index questionsAsked from the 
		// questions vector (which has been randomly shuffled by constructor).
		Question q = questions[questionsAsked];
		
		// Print the text of the question.
		std::cout << q.questionText << std::endl;
		
		// Display the answer choices and get the user's answer
		// using the menu function
		int userAnswer = menu(q.answerChoices);
		
		// Check to see if user answered the question correctly and report the results
		// Increment user's score if they answered correctly.
		if (userAnswer == q.answerNum)
		{
			userScore++;
			std::cout << "Correct!\n";
		}
		else
		{
			std::cout << "Incorrect. The correct answer was: ";
			std::cout << q.answerNum << ": ";
			std::cout << q.answerChoices[(q.answerNum-1)] << std::endl;
		}
		
		
		// Randomly generate 0 or 1 to indicate whether the computer
		// got the question right or wrong.
		bool computerCorrect = static_cast<bool>(getRandomInt(0, 1));
		
		// Report whether or not computer got it right. If they got it right,
		// add a point to their score.
		if (computerCorrect)
		{
			std::cout << computerName << " answered correctly.\n\n";
			computerScore++;
		}
		else
		{
			std::cout << std::endl << computerName << " answered incorrectly.\n\n";
		}	

		// Increment questionsAsked and display updated scores.
		questionsAsked++;

		// Display updated user and computer scores.
		std::cout << "Updated Scores:\n";
		std::cout << "\tYou: " << userScore << std::endl;
		std::cout << "\t" << computerName << " (student): " << computerScore << std::endl;
		
		pressEnter();
	}
	
	// Use a while loop for a tie breaker. Loop as long as the players are
	// tied and it is round 10 or less.
	while (userScore == computerScore && round <= 10)
	{
		std::system("clear");

		// Print round information and current scores
		std::cout << "\t\tRound " << round << "\n\n";
		std::cout << "Scores:\n";
		std::cout << "\tYou: " << userScore << std::endl;
		std::cout << "\t" << computerName << " (student): " << computerScore << std::endl << std::endl;
		
		// Inform user that this is a tie-breaker question
		std::cout << "After " << (round-1) << " questions, it is a tie game.\n\n";
		
		// Get the question at the index questionsAsked from the 
		// questions vector (which has been randomly shuffled by constructor).
		Question q = questions[questionsAsked];
		
		// Print the text of the question.
		std::cout << q.questionText << std::endl;
		
		// Display the answer choices and get the user's answer
		// using the menu function
		int userAnswer = menu(q.answerChoices);
		
		// Check to see if user answered the question correctly and report the results
		// Increment user's score if they answered correctly.
		if (userAnswer == q.answerNum)
		{
			userScore++;
			std::cout << "Correct!\n";
		}
		else
		{
			std::cout << "Incorrect. The correct answer was: ";
			std::cout << q.answerNum << ": ";
			std::cout << q.answerChoices[(q.answerNum-1)] << std::endl;
		}
		
		
		// Randomly generate 0 or 1 to indicate whether the computer
		// got the question right or wrong.
		bool computerCorrect = static_cast<bool>(getRandomInt(0, 1));
		
		// Report whether or not computer got it right. If they got it right,
		// add a point to their score.
		if (computerCorrect)
		{
			std::cout << computerName << " answered correctly.\n\n";
			computerScore++;
		}
		else
		{
			std::cout << std::endl << computerName << " answered incorrectly.\n\n";
		}
	
		// Increment questionsAsked and display updated scores.
		questionsAsked++;

		// Display updated user and computer scores.
		std::cout << "Updated Scores:\n";
		std::cout << "\tYou: " << userScore << std::endl;
		std::cout << "\t" << computerName << " (student): " << computerScore << std::endl;
		
		// Increment round for next while loop iteration
		round++;

		pressEnter();
	}
	
	// Increment the total number of games of trivia played.
	gamesPlayed++;
	
	// Determine if user won, lost, or tied. Report results
	// and set value of moneyWon accordingly.
	int moneyWon = 0;
	
	if (userScore > computerScore)
	{
		std::cout << "Congratulations! You have beaten " << computerName << "! You receive 4 coins.\n";
		moneyWon = 4;
	}
	else if (userScore < computerScore)
	{
		std::cout << "Unfortunately, you have lost this game of trivia and have not earned any money.\n";
		moneyWon = 0;
	}
	else
	{
		std::cout << "Since the game has ended in a tie (even after 5 tie-breaking rounds), you have earned 2 coins.\n";
		moneyWon = 2;
	}
	
	// Depending on whether or not the max number of games have been played,
	// either encourage the user to return to play more
	// or tell them that trivia is done for the day.
	if (gamesPlayed < NUM_GAMES)
	{
		std::cout << "Please come back here again if you want to play more trivia!\n";
	}
	else
	{
		std::cout << "My students need to go home for the day, so that’s it for trivia. Thank you for playing!\n";
	}
	
	pressEnter();

	return moneyWon;
}
