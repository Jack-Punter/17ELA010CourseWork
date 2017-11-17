#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "functions.h"
#include <math.h>

void main()
{
	int outWidth = 1920;
	int outHeight = 1080;
	int nHarmonics = 10;
	//Create the header for the ppm file header,
	char pmmHeader[] = "P3\n%d %d\n255\n";
	//declare an array of pixels the size of the output picture defulting all values to 0,
	int* pixels = calloc(outWidth * outHeight, sizeof(int));
	//declare the poiter for the file
	FILE *pfile = NULL;

	DrawWaves(nHarmonics, pixels, outWidth, outHeight);
	// Draw x axis in white
	for (int x = 0; x < outWidth; x++)
	{
		pixels[(outHeight / 2) * outWidth + x] = rgbInt(255, 255, 255);
	}
	// Open the file
	pfile = fopen("myfile.ppm", "w");
	// Write to the file
	fprintf(pfile, pmmHeader, outWidth, outHeight);
	DrawPixelArray(pfile, pixels, outWidth, outHeight);
	// Close the file and set the pointer to NULL so it cannot be accessed later
	fclose(pfile);
	pfile = NULL;
	// Free the memory used to store the pixels and set the pointer to it NULL so it cannot be accessed later
	free(pixels);
	pixels = NULL;
}