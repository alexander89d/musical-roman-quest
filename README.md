# Project Overview

I completed this project as part of CS 162 (Intro to Computer Science II) during Fall 2018 while I was a student at Oregon State University. **I have been granted express permission by the course instructor to post my source code for this project publicly for use in my online professional portfolio.**

This project implements an Ancient Rome-themed board game with text and ASCII-based graphics. It was developed and tested on a Linux school server. It is written in C++ (C++11 standard; compiled using the G++ compiler).

This is a single-player game. The main objective of the game is that, as a time traveler who has traveled back in time to Ancient Rome, the user must obtain a sound recording of Roman music as well as a copy of Roman sheet music. The board is a 3x3 grid, and the player begins in the center square (the Forum). At the beginning of each turn, a description of the square's purpose is printed, and the user can either "enter" the square to complete a task or simply choose to move on. At the end of the turn, after completing the task at a square or choosing to simply move on, the player must move to any square adjacent to the current square which they occupy. To "win" the game, the player must gain an audience with the emperor, Nero, who resides at the Domus Aurea (Golden Palace) square, in 75 moves or less. The player must figure out what requirements must be met in order to gain admittance to Nero's palace. Certain squares allow the player to earn money. The player can purchase items at the Forum. Other squares have their own special purposes, such as the Campus Martius (Military Training Ground). See [src/Game_Instructions.txt](src/Game_Instructions.txt) for more details about gameplay.

This project reviewed the following major concepts from the course curriculum:
- Inheritance and Polymorphism: There is a Space abstract class with specific types of Spaces as children.
- Composition: The Board class has Spaces, and the Game class that controls the overall execution has a Board.
- Pointers: Each Space has pointers to the spaces to its N, NE, E, SE, S, SW, W, and NW, with null values for any direction representing that there is no space in that direction.
- Text-based Menus: Each time the user is prompted to make a choice (such as to what space they would like to move or what they would like to do at a given space), a menu of choices is printed, and the user enters the number of their choice.

# Repository Structure

The source code for the game is located in the src/ folder. **All files in the src/ directory have not been modified since being submitted as part of this course assignment.** To compile this program on a Linux machine, simply navigate into the src/ directory and use the `make` command. Then, run the program using the command `finalProj`. Finally, the command `make clean` can be used to remove the executable file.

The root directory of this repository also contains the detailed documentation required to be submitted with this project (including a general description of the game, a class heiarchy diagram, pseudocode, a manual testing plan and results, and reflections on changes made from pseudocode during implementation). That documentation can be viewed in [CS162_Final_Project_Documentation.pdf](CS162_Final_Project_Documentation.pdf).
