#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "functions.h"
#include <math.h>

void main()
{
	/*
	Create the header for the ppm file header,
	declare an array of pixels the size of the output picture defulting all values to 0,
	declare the poiter for the file
	*/
	char pmmHeader[] = "P3\n%d %d\n255\n";
	int* pixels = calloc(OUT_WIDTH * OUT_HEIGHT, sizeof(int));
	int numHarmonics = 5000;
	FILE *pfile = NULL;

	DrawWaves(pixels, numHarmonics);
	// Draw x axis in white
	for (int x = 0; x < OUT_WIDTH; x++)
	{
		pixels[(OUT_HEIGHT / 2) * OUT_WIDTH + x] = rgbInt(255, 255, 255);
	}
	// Open, Write to and close the file
	pfile = fopen("myfile.ppm", "w");
	fprintf(pfile, pmmHeader, OUT_WIDTH, OUT_HEIGHT);
	DrawPixelArray(pfile, pixels);
	fclose(pfile);
	free(pixels);
}