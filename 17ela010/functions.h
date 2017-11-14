#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
// define some preprocessor macros to use for the array dimensions
#define OUT_WIDTH 256
#define OUT_HEIGHT 128
#define OUT_DEPTH 3

//Functions to draw to the pixels to the file
void PutPixel(FILE* outFile, int r, int g, int b);
void DrawPixelArray(FILE* outFile, int* arr);
//Function to generate a radom color component (number 0-255)
int RandomColorComponent();
