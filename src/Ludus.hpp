/*************************************************************************************************** 
 * Program Name: Ludus.hpp
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
#ifndef LUDUS_HPP
#define LUDUS_HPP

#include <algorithm>
#include "Space.hpp"

// Constants used by Ludus class
const int NUM_QUESTIONS = 50;		// total number of questions in the questions vector
const int NUM_CHOICES = 4;		// number of answer choices per question
const int NUM_GAMES = 5;		// total number of trivia games that can be played per instance of Game object

class Ludus : public Space
{
	private:
		// Struct that defines a Question object.
		struct Question
		{
			// Data members of struct are string containing text of the question,
			// vector of strings containing answer choices, and an int indicating
			// the number of the correct answer choice.
			std::string questionText;
			std::vector<std::string> answerChoices;
			int answerNum;
		};

		// Private data members
		std::vector<Question> questions;
		std::vector<std::string> studentNames;
		bool obtainedScroll;
		int gamesPlayed;
		int questionsAsked;

		// Private member function
		int play_trivia();

	public:
		// Public member functions
		Ludus();
		virtual ~Ludus();
		virtual void interact(std::set<std::string>& satchel, int& money, int& stepsSinceBathing,
				      bool& hasBathed, bool& knowsAboutScroll, bool& stillAlive, bool& withNero) override;
};
#endif
