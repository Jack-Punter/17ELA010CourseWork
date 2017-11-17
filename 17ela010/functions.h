#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// Define some preprocessor constants
#define PI 3.14159265358979323846f

// Define preproccessor macro to convert degrees to radians
#define RADIANS(x) x*PI/180.0f

//Functions to draw to the pixels to the ppm file
void PutPixel(FILE* outFile, int rgb);
void DrawPixelArray(FILE* outFile, int* arr, int arrWidth, int arrHeight);

//Functions to draw to the array
int CalculateYWithoutOffset(float degrees, int harmonic, int outHeight);
void DrawWaves(int nHarmonics, int* arr, int arrWidth, int arrHeight);

//Functions to generate a random colours
unsigned char RandomColourComponent();
int RandomColour();

// Function to compact colour components into a single int
int rgbInt(unsigned char r, unsigned char g, unsigned char b);