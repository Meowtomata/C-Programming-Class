#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
* Name: Anatoliy Lynevych
* Username: alynevyc
* Description: 
* Program 6 converts characters and numbers to commandsthat draw ASCII art
*/

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

// determine which character to output based on color value
char* draw(double color)
{
    if (color >= 0.9) return "@";
    if (color >= 0.8) return "%";
    if (color >= 0.7) return "#";
    if (color >= 0.6) return "*";
    if (color >= 0.5) return "+";
    if (color >= 0.4) return "=";
    if (color >= 0.3) return "-";
    if (color >= 0.2) return ":";
    if (color >= 0.1) return ".";
    return " ";
}

void printImage(int width, int height, double image[width][height])
{
    // print top border
    printf("+");
    for (int i = 0; i < width; i++)
    {
        printf("-");
    }
    printf("+\n");
    
    // print body of image
    for (int i = 0; i < height; i++)
    {
        printf("|");
        for (int j = 0; j < width; j++)
        {   
            char* b = draw(image[j][i]);
            printf("%s", b);
        }
        printf("|\n");
    }

    // print bottom border
    printf("+");
    for (int i = 0; i < width; i++)
    {
        printf("-");
    }
    printf("+\n");
}

void drawPoint(int width, int height, double image[width][height], int x, int y, double color)
{
    if (x >= width || y >= height || x < 0 || y < 0) return;
    image[x][y] = color;
}

void drawRectangle(int width, int height, double image[width][height], int left, int top, int rectangleWidth, int rectangleHeight, double color)
{
    for (int i = 0; i < rectangleWidth; i++)
    {
        for (int j = 0; j < rectangleHeight; j++)
        {
            drawPoint(width, height, image, left + i, top + j, color);
            
        }
    }
}

void convertToBlackAndWhite(int width, int height, double image[width][height], double threshold)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (image[i][j] >= threshold) image[i][j] = 1.0;
            else image[i][j] = 0.0;
        }
    }
}

void drawLine(int width, int height, double image[width][height], int x1, int y1, int x2, int y2, double color)
{
    // CODE MODIFIED FROM 
    // https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/

    // calculate dx & dy 
    int dx = x2 - x1; 
    int dy = y2 - y1; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps
    double Xinc = dx / (double)steps; 
    double Yinc = dy / (double)steps; 
  
    // Put pixel for each step 
    double X = x1; 
    double Y = y1;

    for (int i = 0; i <= steps; i++) { 
        int x = round(X);
        int y = round(Y);
        
        drawPoint(width, height, image, x, y, color);

        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
    } 
}

void printStats(int width, int height, double image[width][height])
{   
    double sum = 0;
    double min = __DBL_MAX__;
    double max = -__DBL_MAX__;
    int total = width * height;

    // determine min, max, and total sum of image color values
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sum += image[i][j];
            if (image[i][j] < min)
            {
                min = image[i][j];
            }
            if (image[i][j] > max)
            {
                max = image[i][j];
            }
        }
    }

    // determine standard deviation of color values
    double sd = 0;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sd += pow(image[i][j] - sum / total, 2);
        }
    }

    sd = sd / total;
    sd = sqrt(sd);

    // output calculate values
    printf("Color range [%.2f, %.2f], mean %.4f, sd %.4f", min, max, sum / total, sd);
}

void floodFill(int width, int height, double image[width][height], int x, int y, double color)
{   
    // checks if x and y are within bounds
    if (x >= width || x < 0 || y >= height || y < 0)
    {
        return;
    }

    // checks if color is greater than current color
    if (image[x][y] >= color)
    {
        return;
    }

    image[x][y] = color;
    floodFill(width, height, image, x + 1, y, color);
    floodFill(width, height, image, x, y - 1, color);
    floodFill(width, height, image, x, y + 1, color);
    floodFill(width, height, image, x - 1, y, color);


    
}

// Print the resulting greyscale image as ASCII art.
// You need to fix the lines marked with TODO comments to read input from standard input.
// Do not change other things in the main function.
int main(void)
{
    // Read in the size of the drawing canvas
    int width = 0;
    int height = 0;
        
    // scanf function returns an integer with the number of read in variables
    int result = scanf(" %d %d", &width, &height);
    
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
                result = scanf(" %d %d %lf", &x, &y, &color);
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
                result = scanf(" %d %d %d %d %lf", &left, &top, &rectangleWidth, &rectangleHeight, &color); 
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
                result = scanf("%lf", &threshold); 
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
                result = scanf(" %d %d %d %d %lf", &x1, &y1, &x2, &y2, &color); 
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
                result = scanf(" %d %d %lf", &x, &y, &color); 
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



