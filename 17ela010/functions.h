#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
// define some preprocessor constants
#define OUT_WIDTH 1920
#define OUT_HEIGHT 256
#define PI 3.1415926f
#define PI_2 3.1415926f / 2.0f

// Define preproccessor macro to convert degrees to radians
#define RADIANS(x) x*PI/180.0f

//Functions to draw to the pixels to the file
void PutPixel(FILE* outFile, int rgb);
void DrawPixelArray(FILE* outFile, int* arr);

//Functions to draw to the array
int CalculateYWithoutOffset(float degrees, int harmonic);
void DrawWaves(int* arr, int nHarmonics);

//Functions to generate a random colours
unsigned char RandomColourComponent();
int RandomColour();

// Function to compact colour components into a single int
int rgbInt(unsigned char r, unsigned char g, unsigned char b);