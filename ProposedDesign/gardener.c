#include "gardener.h"
//stdlib, lawnholder, output

/*
struct _pointlist
	{
	int x;
	int y;
	struct _pointlist *next;
	};
typedef struct _pointlist pointlist;

struct _reclist
	{
	int x1;
	int y1;
	int x2;
	int y2;
	struct _reclist *next;
	}
typedef struct _reclist reclist;
*/

void ResetSignsJump(char **Lawn, int xsize, int ysize)
	{
	for(int j = 0; j < ysize; j++)
		{
		for(int i = 0; i < xsize; i++)
			*(*(Lawn+JUMP*i)+JUMP*j) = -(*(*(Lawn+JUMP*i)+JUMP*j));
		}
	}

void SignAreaJump(char **Lawn, int xsize, int ysize, int i, int j)
	{
	*(*(Lawn+JUMP*i)+JUMP*j) = -(*(*(Lawn+JUMP*i)+JUMP*j));
	if(i + 1 < xsize && *(*(Lawn+JUMP*(i+1))+JUMP*j) == 1)
		SignAreaJump(Lawn, xsize, ysize, i + 1, j);
	if(i - 1 >= 0 && *(*(Lawn+JUMP*(i-1))+JUMP*j) == 1)
		SignAreaJump(Lawn, xsize, ysize, i - 1, j);
	if(j + 1 < ysize && *(*(Lawn+JUMP*i)+JUMP*(j+1)) == 1)
		SignAreaJump(Lawn, xsize, ysize, i, j + 1);
	if(j - 1 >= 0 && *(*(Lawn+JUMP*i)+JUMP*(j-1)) == 1)
		SignAreaJump(Lawn, xsize, ysize, i, j - 1);
	}

pointlist *NewPoint(int x, int y, pointlist *next)
	{
	pointlist *outcome = malloc(sizeof(*outcome));
	if(outcome == NULL)
		return NULL;
	outcome -> x = x;
	outcome -> y = y;
	outcome -> next = next;
	return outcome;
	}

void FreePoints(pointlist *point)
	{
	pointlist *piv;
	while(point != NULL)
		{
		piv = point -> next;
		free(point);
		point = piv;
		}
	}

pointlist *FindAreas(char **Lawn, int xsize, int ysize)
	{
	pointlist *ret = NULL
	for(int j = 0; j < ysize; j++)
		{
		for(int i = 0; i < xsize; i++)
			{
			if(*(*(Lawn+JUMP*i)+JUMP*j) == 1)
				{
				pointlist *piv = NewPoint(i, j, ret);
				if(piv == NULL)
					{
					FreePoints(ret);
					return NULL;
					}
				ret = piv;
				SignAreaJump(Lawn, xsize, ysize, i, j);
				}
			}
		}
	ResetSignsJump(Lawn, xsize, ysize);
	return ret;
	}

void FreeRectangles(reclist *rec)
	{
	reclist *piv;
	while(rec != NULL)
		{
		piv = rec -> next;
		free(rec);
		rec = piv;
		}
	}

int CalcLenRight(char **Lawn, int x, int y, int xsize)
	{
	int i = x + 1;
	while(i < xsize && *(*(Lawn+JUMP*i)+JUMP*y) != 0)
		i++;
	return i - x;
	}

int CheckRow(char **Lawn, int x, int y, int len, int xsize, int ysize)
	{
	if(y == ysize)
		return 1;
	if(x - 1 >= 0 && *(*(Lawn+JUMP*(x-1))+JUMP*y) != 0)
		return 1;
	int i = 0;
	while(i < len)
		{
		if(*(*(Lawn+JUMP*(x+i))+JUMP*y) == 0)
			return 1;
		i++;
		}
	if(x + i < xsize && *(*(Lawn+JUMP*(x+i))+JUMP*y) != 0)
		return 1;
	return 0;
	}

int UpDownRectangle(char **Lawn, int x, int y, int xsize, int ysize, reclist *rectangles)
	{
	rectangles -> x1 = x;
	rectangles -> y1 = y;
	int len = CalcLenRight(Lawn, x, y, xsize);
	int j = y + 1;
	int isend = CheckRow(Lawn, x, j, len, xsize, ysize);
	while(isend == 0)
		{
		j++;
		isend = CheckRow(Lawn, x, j, len, xsize, ysize);
		}
	rectangles -> x2 = x + len - 1;
	rectangles -> y2 = j - 1;
	return 1;
	}

int DoTheJob(char **Lawn, parameters *Param, sprlist *Sprinklers);
	{
	pointlist *areas = FindAreas(Lawn, Param->xsize/JUMP, Param->ysize/JUMP);
	pointlist *pivareas = areas;
	if(areas == NULL)
		return 0;
	while(areas != NULL)
		{
		reclist *rectangles = malloc(sizeof(*rectangles));
		if(rectangles == NULL)
			{
			FreePoints(pivareas);
			return 0;
			}
		int errcode = UpDownRectangle(Lawn, areas->x, areas->y, Param->xsize/JUMP, Param->ysize/JUMP, rectangles);
		if(errcode == 0)
			{
			FreeRectangles(rectangles);
			FreePoints(pivareas);
			return 0;
			}
		//
		FreeRectangles(rectangles);
		areas = areas -> next;
		}
	FreePoints(pivareas);
	return 1;	
	}
