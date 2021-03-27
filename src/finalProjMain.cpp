/*************************************************************************************************************** 
 * Program Name: finalProjMain.cpp
 * Author: Alexander Densmore
 * Date: 12/3/18
 * Description: This program implements a game with linked spaces that is set in Ancient Rome. 
 * 		The board is a 3 x 3 grid of 9 spaces, each space being of a different type. The user takes on 
 * 		the role of a time traveler who has gone to Ancient Rome to research Roman music (although it 
 * 		is known that Roman music existed, little is known about what it would have actually sounded 
 * 		like). The user must visit the emperor Nero for dinner, record him singing, and get a copy 
 * 		of written music from him. However, there are challenges the user must overcome before they 
 * 		will be given permission to visit Nero. They have 75 total steps to go between the spaces, 
 * 		complete the tasks, and collect the items necessary to get an audience with Nero. 
 * 		The user must be careful, because certain actions (such as fighting gladiator battles) 
 * 		could result in their characters death and the end of the game regardless of the number of 
 * 		steps taken so far.
 **************************************************************************************************************/
#include "Game.hpp"

int main()
{
	// Declare a bool variable "playAgain" for use in the do-while loop that 
	// iterates once for each game played until the user chooses to quit.
	bool playAgain = false;
	
	do
	{	
		// Clear the screen for printing of game instructions.
		std::system("clear");
		
		// Load each line of instructions in from the instructions file,
		// pausing and having the user press enter every time
		// the delimination character is reached.
		std::ifstream inputFile("Game_Instructions.txt");
		std::string text;
		while (getline(inputFile, text, DELIM))
		{
			std::cout << text;
			pressEnter();
		}
		inputFile.close();

		// Create a new Game object (a new Game is therefore created during
		// and destroyed at the end of each iteration of this outer do-while loop).
		Game myGame;

		// Loop to have the user take turns until the Game class signals that the Game is over
		// (which occurs when the user dies, reaches the step limit,
		// or wins the game).
		do
		{
			myGame.take_turn();
		} while(myGame.game_over() == false);

		// Use the menu function to ask the user if they want to play again.
		std::vector<std::string> mainMenu = {"Play again", "Exit"};	
		std::cout << "Main Menu: " << std::endl;
		int mainChoice = menu(mainMenu);
		
		// Process the user's choice.
		if (mainChoice == 1)
		{
			playAgain = true;
		}
		else
		{
			playAgain = false;
		}

	} while (playAgain);

	return 0;
}
