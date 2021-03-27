/**************************************************************************************** 
 * Program Name: getRandomInt.hpp
 * Author: Alexander Densmore
 * Date: 10/1/18
 * Description: Header file for function that accepts lower bound and upper bound
 * 		of desired randomized integer as parameters (randomized integer can be
 * 		greater than or equal to lower bound and less than or equal to upper
 * 		bound). Function returns the randomly generated
 * 		integer within those bounds.
 ***************************************************************************************/
#ifndef GETRANDOMINT_HPP
#define GETRANDOMINT_HPP

#include <cstdlib>
#include <ctime>

int getRandomInt(int lowerBound, int upperBound);

#endif
