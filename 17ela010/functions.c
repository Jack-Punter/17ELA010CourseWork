/*
17ELA010 C Coursework
https://github.com/JackPunter/17ELA010CourseWork

Author: B726243, Jack Punter
Date: 21-11-17
*/

#include "functions.h"
#include <math.h>

void PutPixel(FILE* outFile, const int rgb)
{
	// 0xFF & (bitwise AND) is used to only take the value of the first byte of the integer
	// -3 Used to right align the numbers for readabilty of the ppm file, does not affect actuall image
	// Print red component
	fprintf(outFile, "%-3d ", 0xFF & rgb >> 16);
	// Print green component
	fprintf(outFile, "%-3d ", 0xFF & rgb >> 8);
	// Print blue component
	fprintf(outFile, "%-3d ", 0xFF & rgb);
	// Print a tab to seperate pixels for easier file reading by human
	fprintf(outFile, "\t");
}

unsigned char RandomColourComponent()
{
	// return a random number between 0 and 255
	int random = rand();
	return random % 256;
}

int RandomColour()
{
	//return a random colour int
	return rgbInt(RandomColourComponent(), RandomColourComponent(), RandomColourComponent());
}

void DrawPixelArray(FILE* outFile, const int* arr, const int arrWidth, const int arrHeight)
{
	// loop through the array an write each colour to the file
	for (int y = 0; y < arrHeight; y++)
	{
		for (int x = 0; x < arrWidth; x++)
		{
			PutPixel(outFile, arr[y * arrWidth + x]);
		}
		fprintf(outFile, "\n");
	}
}

int CalculateYWithoutOffset(const float radians, const int harmonic, const int outHeight)
{
	//Calculate the harmonic factor to be used in the calculation of the y values
	int k = 2 * harmonic - 1;

	/* Calculate y value
	Add PI to the angle to translate the graph so it draws properly
	-  Done because going up in y goes down the output image
	Multiply by half the height of the output image
	- minus a buffer to acomodate for peeks in the square wave being greater than the first harmonic
	Then add half the height of the output image to move the wave to be centered in the middle of the output image
	*/
	return (int)(((outHeight / 2.0f - 10) * sinf(PI + radians * k)) / k);
}

void DrawWaves(const int nHarmonics, int* arr, const int arrWidth, const int arrHeight)
{
	// Make the square wave green
	int squareCol = rgbInt(0, 255, 0);

	// Allocate memory for the colours of each harmonic
	int* col = calloc(nHarmonics, sizeof(int));

	// Assign each harmonic with a random colour
	for (int harmonic = 0; harmonic < nHarmonics; harmonic++)
	{
		col[harmonic] = RandomColour();
	}

 	for (int x = 0; x < arrWidth; x++)
	{
		// Calculate the radians for the sin once per X
		float radians = ((float)x / (float)arrWidth) * 4 * PI;
		int squareY = 0;

		// Loop through each harmonic calculating the Y positions and then add that to the Y position of the square wave
		for (int harmonic = 1; harmonic <= nHarmonics; harmonic++)
		{
			int y = CalculateYWithoutOffset(radians, harmonic, arrHeight);
			squareY += y;
			// Offset the y value to centre the harmonic wave and plot
			y += arrHeight / 2;
			arr[y * arrWidth + x] = col[harmonic - 1];
		}
		// Multiply the sum of the harmonic waves by 4/PI as stated by the equation given
		squareY *= (int)(4.0f / PI);
		// Offset the y value to centre the square wave and plot
		squareY += arrHeight / 2;
		arr[squareY * arrWidth + x] = squareCol;
	}
	// Free the memory allocated for the wave colours
	free(col);
	col = NULL;
}

int rgbInt(const unsigned char r, const unsigned char g, const unsigned char b)
{
	// Use bitwise OR to combine the 3 0-255 values into a single int
	return r << 16 | g << 8 | b;
}

void getNumberMax(int* output, char* errorBuffer, const char* prompt, const int max)
{
	// Double to get user input, will be cast to an int
	// Allow the user to input a double without reading by multiple scanfs
	double dInput;
	enum bool valid;
	// Get the user input for the number of harmonics to use
	do
	{
		// Set the initial state of the valid bool to be true
		valid = true;
		// Prompt the user for an input
		printf(prompt);
		// Get the input and check if the return code from scanf is 0 or negative (invalid input)
		if (scanf("%lf", &dInput) <= 0)
		{
			// If it was, read the input into a string and return an error to the user
			scanf("%s", errorBuffer);
			printf("\nYour input of:\n\"%s\"\nis invalid. Please re-enter\n\n", errorBuffer);
			// Set the valid bool to false so that the user is prompted for input again
			valid = false;
		}

		// Validate that the user has entered a sensible number of harmonics
		if (dInput > max)
		{
			printf("Input must not be greater than %d\n", max);
			valid = false;
		}
		// If they did, cast the input to an integer and set nHarmonics to the input
		else
		{
			*output = (int)dInput;
		}
		// Loop until the input was all valid
	} while (valid == false);
}

void getPositiveNumberMax(int* output, char* errorBuffer, const char* prompt, const int max)
{
	enum bool valid = true;
	
	do
	{
		// Gets a number
		getNumberMax(output, errorBuffer, prompt, max);
		// if the number is 0 or negative it is an invalid input
		if (output <= 0)
		{
			printf("Your input must be positive and non-zero.");
			valid = false;
		}
	} while (valid == false);
}
