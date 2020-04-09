#ifndef LAWNHOLDER
#define LAWNHOLDER

#include <stdlib.h>
//#include "output.h"

/*
 * Structure for holding lawn's parameters
 */
typedef struct _parameters
	{
	int xsize;
	int ysize;
	int pixelsize; //size of one character in the array
	int nlawn;	//Number of waterable pixels
	int time;	//time spent on watering
	int radius360;	//radius of 360 sprinkler
	double currentmean;
	} parameters;

/*
 * Calculates arithmetic mean of pixel's waterlvl in Lawn
 *
 * char **Lawn - matrix that stores lawn's pixels
 *
 * parameters *Param - points to structure that holds
 * lawn's parameters
 *
 * Function does not update currentmean field in parameters
 * structure. Returns said mean.
 */
//double CalculateMean(char **Lawn, parameters *Param);

/*
 * Places sprinkler and waters the lawn
 *
 * char **Lawn - matrix that stores lawn's pixels
 *
 * int type - sprinkler's type (90/180/270/360)
 *
 * int time - duration of watering
 *
 * int x, y - sprinkler's coordinates
 *
 * int deg - degree between OX and circular's segment "arm" -
 * the one that is nearer OX when circular segment is placed
 * with rounded side upwards
 *
 * sprlist *Sprinklers - list of already placed sprinklers
 *
 * Returns 0 on failure
 */
//int PutSprinkler(char **Lawn, int type, int time, int x, int y, int deg, sprlist *Sprinklers);

#endif