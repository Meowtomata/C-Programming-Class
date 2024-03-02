// Student stub code for ASCII Drawing assignment

#include <stdio.h>
#include <stdlib.h>

// Initializes all the pixels of an image to black.
void initImage(int width, int height, double image[width][height])
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            image[x][y] = 0.0;
        }
    }
}

// TODO: add a parameter list and implementation for the remaining functions.
// Check the calls in the main function to figure out the order and types of 
// the parameters that are passed to each function.

void printImage(int width, int height, double image[width][height])
{
}

void drawPoint(int width, int height, double image[width][height], int x, int y, double color)
{
}

void drawRectangle(int width, int height, double image[width][height], int left, int top, int rectangleWidth, int rectangleHeight, double color)
{
}

void convertToBlackAndWhite(int width, int height, double image[width][height], double threshold)
{
}

void drawLine(int width, int height, double image[width][height], int x1, int y1, int x2, int y2, double color)
{
}

void printStats(int width, int height, double image[width][height])
{
}

void floodFill(int width, int height, double image[width][height], int x, int y, double color)
{
}

// Print the resulting greyscale image as ASCII art.
// You need to fix the lines marked with TODO comments to read input from standard input.
// Do not change other things in the main function.
int main(void)
{
    // Read in the size of the drawing canvas
    int width = 0;
    int height = 0;
        
    // TODO: replace 0 with a call to scanf that reads in both the width and height.
    // The scanf function returns an integer with the number of read in variables.
    // The main program uses this result to check for badly formatted input.
    // The scanf function can read in multiple variables in one call (see the lecture slides).
    int result = 0;
    
    // Program only supports images that are 1x1 or bigger
    if ((width <= 0) || (height <= 0) || (result != 2))
    {
        printf("Failed to read a valid width and height from standard input!\n");
        return 0;
    }
    
    // Create the 2D array and initialize all the greyscale values to 0.0.
    // The first dimension is the x-coordinate.
    // The second dimension is the y-coordinate.
    double image[width][height];
    initImage(width, height, image);
    
    char command = '\0';
    double color = 0.0;
    
    // Keep reading in drawing commands until we reach the end of the input
    while (scanf(" %c", &command) == 1)
    {
        switch (command)
        {		
            case 'p': 	
            {
                // Draw a point, read in: x, y, color
                int x = 0;
                int y = 0;
                result = 0; // TODO: fix
                if (result != 3)
                {
                    printf("Invalid point command!\n");
                    return 0;
                }
                drawPoint(width, height, image, x, y, color);
                break;
            }
            case 'r': 	
            {
                // Draw a rectangle, read in: x, y, w, h, color
                int left = 0;
                int top = 0;
                int rectangleWidth = 0;
                int rectangleHeight = 0;
                result = 0; // TODO: fix
                if (result != 5)
                {
                    printf("Invalid rectangle command!\n");
                    return 0;
                }
                drawRectangle(width, height, image, left, top, rectangleWidth, rectangleHeight, color);
                break;
            }
            case 'b':   
            {
                // Convert to black and white
                double threshold = 0.0;
                result = 0; // TODO: fix
                if (result != 1)
                {
                    printf("Invalid black and white command!\n");
                    return 0;
                }
                convertToBlackAndWhite(width, height, image, threshold);
                break;
            }

            case 'l':
            {
                // Draw a line, read in x1, y1, x2, y2, color
                int x1 = 0;
                int y1 = 0;
                int x2 = 0;
                int y2 = 0;      
                result = 0; // TODO: fix
                if (result != 5)
                {
                    printf("Invalid line command!\n");
                    return 0;
                }
                drawLine(width, height, image, x1, y1, x2, y2, color);
                break;
            }            
            case 'f':
            {
                // Flood fill a color in, read in: x, y, color
                int x = 0;
                int y = 0;
                result = 0; // TODO: fix
                if (result != 3)
                {
                    printf("Invalid flood fill command!\n");
                    return 0;
                }
                floodFill(width, height, image, x, y, color);
                break;
            }
            default:
            {
                printf("Unknown command!\n");
                return 0;
            }
        }
    }
	
    // Print the final image
    printImage(width, height, image);
    
    // Finally display some statistics about the image
    printStats(width, height, image);

    return 0;
}



