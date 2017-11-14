#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "functions.h"

void main()
{
	/*
	Create the header for the ppm file headder,
	declare an array of pixels the size of the output picture
	open the file that we will write the image to 
	*/
	char pmmHeader[] = "P3\n%d %d\n255\n";
	int pixels[OUT_WIDTH * OUT_HEIGHT * OUT_DEPTH];
	FILE *pfile = fopen("myfile.ppm", "w");

	//Loop through the array and fill each colour component with a random value from 0 - 255
	for (int y = 0; y < OUT_HEIGHT; y++)
	{
		for (int x = 0; x < OUT_WIDTH; x++)
		{
			for (int z = 0; z < OUT_DEPTH; z++)
			{
				pixels[OUT_DEPTH * (x + y * OUT_WIDTH) + z] = RandomColorComponent();
			}
		}
	}

	// Write to the file and close the file
	fprintf(pfile, pmmHeader, OUT_WIDTH, OUT_HEIGHT);
	DrawPixelArray(pfile, pixels);
	fclose(pfile);
}