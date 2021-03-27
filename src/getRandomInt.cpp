/**************************************************************************************** 
 * Program Name: getRandomInt.cpp
 * Author: Alexander Densmore
 * Date: 10/1/18
 * Description: Implementation file for function that accepts lower bound and upper bound
 * 		of desired randomized integer as parameters (randomized integer can be
 * 		greater than or equal to lower bound and less than or equal to upper
 * 		bound). Function returns the randomly generated
 * 		integer within those bounds.
 ***************************************************************************************/
#include "getRandomInt.hpp"

int getRandomInt(int lowerBound, int upperBound)
{
	// Use "time" function to get random seed for rand()
	// function. Seed the rand() function with that seed.
	// Only seed rand() the first time this function is called to avoid
	// repeatedly generating the same random value
	// since this function may be called many times per second.
	static bool firstCall = true;
	if (firstCall == true)
	{
		unsigned seed = time(0);
		srand(seed);
		firstCall = false;
	}

	// Generate a random number within the desired range.
	int randomInt = (rand() % (upperBound - lowerBound + 1)) + lowerBound;

	// Return the randomly generated number to the calling function.
	return randomInt;
}
