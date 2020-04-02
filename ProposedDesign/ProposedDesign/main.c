#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "lawnholder.h"
#include "gardener.h"
#include "output.h"

void FreeMemory(FILE *lawnfile, char **Lawn, parameters *Param)
	{
	fclose(lawnfile);
	//(...)
	}

int main(int argc, char *args[])
	{
    int errCode = 0;
	if(argc <= 1)
		{
		fprintf(stderr, "No input file\n");
		return EXIT_FAILURE;
		}
	FILE *lawnfile = fopen(args[1], "r");
	if(lawnfile == NULL)
		{
		fprintf(stderr, "Couldn't open input file\n");
		return EXIT_FAILURE;
		}
	char **Lawn;
	parameters Param;
	errCode = InitializeParameters(lawnfile, &Param, argc>2 ? atoi(argc[3]) : 100 );
	if (errCode != 0)
    {
        return EXIT_FAILURE;
    }
	rewind(lawnfile);
	errCode = CreateLawn(lawnfile, &Param, Lawn);
	if (errCode != 0)
    {
        return EXIT_FAILURE;
    }
	fclose(lawnfile);
	if(Lawn == NULL)
		{
		FreeMemory(lawnfile, Lawn, &Param);
		fprintf(stderr, "Memory allocation error\n");
		return EXIT_FAILURE;
		}

	sprlist Sprinklers;
	if(DoTheJob(Lawn, &Param, &Sprinklers) == 0)
		{
		FreeMemory(lawnfile, Lawn, &Param);
		fprintf(stderr, "The Job could not be done\n");
		return EXIT_FAILURE;
		}

	FILE *bitmap = fopen("BITMAP.bmp", "wb");
	FILE *output = fopen("SPRINKLERSPLACEMENT", "w");
	if(bitmap == NULL || output == NULL)
		{
		FreeMemory(lawnfile, Lawn, &Param);
		fclose(bitmap);
		fclose(output);
		fprintf(stderr, "Could not open output files\n");
		return EXIT_FAILURE;
		}
	if(CreateBitmap(bitmap, Lawn, &Param) == 0)
		{
		FreeMemory(lawnfile, Lawn, &Param);
		fclose(bitmap);
		fclose(output);
		fprintf(stderr, "Could not create bitmap\n");
		return EXIT_FAILURE;
		}
	CreateOutputFile(output, &Sprinklers);

	return EXIT_SUCCESS;
	}