#include "functions.h"

void PutPixel(FILE * outFile, int r, int g, int b)
{
	fprintf(outFile, "%-3d %-3d %-3d  ", r, g, b);
}

int RandomColorComponent()
{
	int random = rand();
	return random % 256;
}

void DrawPixelArray(FILE* outFile, int* arr)
{
	// loop through the array an write each color component to the file
	for (int y = 0; y < OUT_HEIGHT; y++)
	{
		for (int x = 0; x < OUT_WIDTH; x++)
		{
			for (int z = 0; z < OUT_DEPTH; z++)
			{
				fprintf(outFile, "%-3d ", arr[OUT_DEPTH * (x + y * OUT_WIDTH) + z]);
			}
			fprintf(outFile, "\t");
		}
		fprintf(outFile, "\n");
	}
}