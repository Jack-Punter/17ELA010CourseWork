#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

/*
17ELA010 C Coursework
https://github.com/JackPunter/17ELA010CourseWork

Author: B726243, Jack Punter
Date: 21-11-17
*/

#include <stdio.h>

// Define some preprocessor constants
#define PI 3.14159265358979323846f

// Enumeration to represent a true or false value - Boolean
enum bool
{
	false,
	true
};

//Functions to draw to the pixels to the ppm file
void PutPixel(FILE* outFile, const int rgb);
void DrawPixelArray(FILE* outFile, const int* arr, const int arrWidth, const int arrHeight);

//Functions to draw to the array
int CalculateYWithoutOffset(const float radians, const int harmonic, const int outHeight);
void DrawWaves(const int nHarmonics, int* arr, const int arrWidth, const int arrHeight);

//Functions to generate a random colours
unsigned char RandomColourComponent();
int RandomColour();

// Function to compact colour components into a single int
int rgbInt(const unsigned char r, const unsigned char g, const unsigned char b);

// User input functions
// Gets a number < max
void getNumberMax(int* output, char* errorBuffer, const char* prompt, const int max);
// Gets a number < max and > 0
void getPositiveNumberMax(int* output, char* errorBuffer, const char* prompt, const int max);
// Wrapper function to get number of harmonics without having to use prompt
void getHarmonics(int* output, char* errorBuffer, const int max);