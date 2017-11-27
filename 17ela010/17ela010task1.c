#define _CRT_SECURE_NO_WARNINGS

/*
17ELA010 C Coursework
https://github.com/JackPunter/17ELA010CourseWork

Drawing sine wave harmonics and square wave acheived by summing the waves

Author:	B726243, Jack Punter
Date:	21-11-17
*/

#include <stdio.h>
#include "functions.h"
#include <math.h>

void main()
{
	//Create the header for the ppm file header
	char pmmHeader[] = "P3\n%d %d\n255\n";
	int maxFileWidth = 10000;
	int maxFileHeight = 10000;
	int maxHarmonics = 10000;
	// Create variables for user to declare
	int outWidth;
	int outHeight;
	int nHarmonics;
	char fileName[32];
	// Create the pointers to the pixel array and the file
	FILE* pfile = NULL;
	int* pixels = NULL;
	// Declare and initialise an array to store any invalid inputs that the user writes.
	char inputErrorBuffer[64] = { 0 };
	// Boolean to be used for input stages to ensure the user inputs valid data
	enum bool valid;
	
	// Get a number for the number of harmonics to use
	getNumberMax
	(
		&nHarmonics,
		inputErrorBuffer,
		"Input 0 or negative to exit the program.\nInput the number of harmonics you would like to use: ", 
		maxHarmonics
	);

	while (nHarmonics >= 0)
	{
		// Get dimensions of the output image from the user
		// Get the width of the image
		getPositiveNumberMax
		(
			&outWidth,
			inputErrorBuffer,
			"Input the width of the output image: ",
			maxFileWidth
		);

		// Get the height of the image
		getPositiveNumberMax
		(
			&outHeight,
			inputErrorBuffer,
			"Input the hight of the output image: ",
			maxFileHeight
		);

		do
		{
			valid = true;
			// Get the user to input the file to write to
			printf("Input the name of the file you would like to draw to (DO NOT USE SPACES): ");
			scanf("%s", &fileName);
			strcat(fileName, ".ppm");

			// Open the file
			printf("Opening the file...\n");
			pfile = fopen(fileName, "w");

			// Check if opening the file failed
			if (pfile == NULL)
			{
				printf("Something went wrong opening the file\nTry a different file name using NO WHITESPACE\n");
				valid = false;
			}
		} while (valid == false);

		printf("Allocating memory for pixel array...\n");
		// Allocate an array of pixels the size of the output image (defult values will be 0)
		pixels = calloc(outWidth * outHeight, sizeof(int));

		// Draw to the pixel array
		printf("Calculating and drawing waves to the array...\n");
		DrawWaves(nHarmonics, pixels, outWidth, outHeight);
		// Draw x axis in white
		printf("Drawing x axis on image...\n");
		for (int x = 0; x < outWidth; x++)
		{
			pixels[(outHeight / 2) * outWidth + x] = rgbInt(255, 255, 255);
		}

		// Write to the file
		printf("Writing to the file...\n");
		fprintf(pfile, pmmHeader, outWidth, outHeight);
		DrawPixelArray(pfile, pixels, outWidth, outHeight);

		// Memory cleanup
		printf("Closing file and freeing memory...\n");
		// Close the file and set the pointer to NULL so it cannot be accessed later
		fclose(pfile);
		pfile = NULL;
		// Free the memory used to store the pixels and set the pointer to it NULL so it cannot be accessed later
		free(pixels);
		pixels = NULL;
		printf("File Generated!\n\n");

		getNumberMax
		(
			&nHarmonics,
			inputErrorBuffer,
			"Input 0 or negative to exit the program.\nInput the number of harmonics you would like to use: ",
			maxHarmonics
		);
	}
}