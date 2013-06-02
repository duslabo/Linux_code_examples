/**
 * @file structure_basic.h
 * @brief This header file contains all required
 * functions and structure declarations.
 * @author Jeshwanth
 * @date 02/06/2013
 */

#ifndef STRUCTURE_BASIC_H_
#define STRUCTURE_BASIC_H_

/**
 * @brief struct point holds two coordinates
 */
struct point
{
	int x;
	int y;
};

/**
 * @brief struct rectangle holds two point structure.
 */
struct rectangle
{
	struct point p1;
	struct point p2;
};

/**
 *@brief struct key that holds word and count.
 */
struct key
{
	char* word;
	int count;
};

/**
 * @brief Function For Addition.
 */
int add( int x, int y);

/**
 * @brief Function for Subtraction.
 */
int sub( int x, int y);

#endif /* STRUCTURE_BASIC_H_ */
