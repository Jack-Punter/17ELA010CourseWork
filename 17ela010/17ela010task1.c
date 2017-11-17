#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "functions.h"
#include <math.h>

void main()
{	
	//Create the header for the ppm file header,
	char pmmHeader[] = "P3\n%d %d\n255\n";
	// Create variables for user to declare;
	int outWidth;
	int outHeight;
	int nHarmonics;
	char fileName[32];

	// Get the user input for the number of harmonics to use
	printf("Input -1 to exit the program.\nInput the number of harmonics you would like to use to generate the square wave: ");
	scanf("%d", &nHarmonics);

	while (nHarmonics > 0)
	{
		// Get dimensions of the output image from the user
		printf("Input the width of the output image: ");
		scanf("%d", &outWidth);
		printf("Input the height of the output image: ");
		scanf("%d", &outHeight);

		// Get the user to input the file to write to
		printf("Input the name of the file you would like to draw to (DO NOT USE SPACES): ");
		scanf("%s", &fileName);

		printf("Allocating memory for pixel array...\n");
		//declare an array of pixels the size of the output picture defulting all values to 0,
		int* pixels = calloc(outWidth * outHeight, sizeof(int));

		printf("Calculating and drawing waves to the array...\n");
		DrawWaves(nHarmonics, pixels, outWidth, outHeight);
		// Draw x axis in white
		printf("Drawing x axis on image...\n");
		for (int x = 0; x < outWidth; x++)
		{
			pixels[(outHeight / 2) * outWidth + x] = rgbInt(255, 255, 255);
		}

		// Open the file
		printf("Opening and writing to file...\n");
		FILE *pfile = fopen(fileName, "w");
		// Write to the file
		fprintf(pfile, pmmHeader, outWidth, outHeight);
		DrawPixelArray(pfile, pixels, outWidth, outHeight);
		
		printf("Closing file and freeing memory...\n");
		// Close the file and set the pointer to NULL so it cannot be accessed later
		fclose(pfile);
		pfile = NULL;
		// Free the memory used to store the pixels and set the pointer to it NULL so it cannot be accessed later
		free(pixels);
		pixels = NULL;
		printf("File Generated!\n\n");

		// Get the user input for the number of harmonics to use
		printf("Input -1 to exit the program.\nInput the number of harmonics you would like to use to generate the square wave: ");
		scanf("%d", &nHarmonics);
	}
}