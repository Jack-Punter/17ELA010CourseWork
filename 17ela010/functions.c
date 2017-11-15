#include "functions.h"
#include <math.h>

void PutPixel(FILE* outFile, int rgb)
{
	// Print red component
	fprintf(outFile, "%-3d ", 0xFF & rgb >> 16);
	// Print green component
	fprintf(outFile, "%-3d ", 0xFF & rgb >> 8);
	// Print blue component
	fprintf(outFile, "%-3d ", 0xFF & rgb);
	// Print a tab to seperate pixels for easier file reading by human
	fprintf(outFile, "\t");
}

unsigned char RandomColorComponent()
{
	// return a random number between 0 and 255
	int random = rand();
	return random % 256;
}

int RandomColor()
{
	//return a random color int
	return rgbInt(RandomColorComponent(), RandomColorComponent(), RandomColorComponent());
}

void DrawPixelArray(FILE* outFile, int* arr)
{
	// loop through the array an write each color to the file
	for (int y = 0; y < OUT_HEIGHT; y++)
	{
		for (int x = 0; x < OUT_WIDTH; x++)
		{
			PutPixel(outFile, arr[y * OUT_WIDTH + x]);
		}
		fprintf(outFile, "\n");
	}
}

int CalculateYWithoutOffset(float radians, int harmonic)
{
	//Calculate the harmonc factor to be used in the calculation of the y values
	float k = 2 * harmonic - 1;

	/* Calculate y value
	Add PI to the angle to translate the graph so it draws properly
	-  Done because going up in y goes down the output image
	Multiply by half the height of the output image
	- minus a buffer to acomodate for peeks in the square wave being greater than the first harmonic
	Then add half the height of the output image to move the wave to be centered in the middle of the output image
	*/
	return (int)(((OUT_HEIGHT / 2.0f - 10) * sinf(PI + radians * k)) / k);
}

void DrawWaves(int* arr, int nHarmonics)
{
	int squareCol = RandomColor();
	int* col = calloc(nHarmonics, sizeof(int));
 	for (int x = 0; x < OUT_WIDTH; x++)
	{
		// Calculate the radians for the sin once per X
		float degrees = ((float)x / (float)OUT_WIDTH) * 720;
		float radians = RADIANS(degrees);
		int squareY = 0;

		for (int harmonic = 1; harmonic <= nHarmonics; harmonic++)
		{
			col[harmonic - 1] = col[harmonic - 1] <= 0 ? RandomColor() : col[harmonic - 1];
			int y = CalculateYWithoutOffset(radians, harmonic);
			squareY += y;
			y += OUT_HEIGHT / 2;
			arr[y * OUT_WIDTH + x] = col[harmonic - 1];
		}
		squareY *= (int)(4.0f / PI);
		squareY += OUT_HEIGHT / 2;
		arr[squareY * OUT_WIDTH + x] = squareCol;
	}
	free(col);
}

int rgbInt(unsigned char r, unsigned char g, unsigned char b)
{
	return r << 16 | g << 8 | b;
}