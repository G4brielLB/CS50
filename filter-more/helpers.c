#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporary[height][width];
    // Reflecting the image to a temporary one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temporary[i][(width - 1) - j] = image[i][j];
        }
    }
    // Passing the reflected image in temporary to the main one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temporary[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporary[height][width];
    // Loop through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Defining variables (rows, columns, amound of rgb pixels and counts)
            int rowPlace[] = {i - 1, i, i + 1};
            int colPlace[] = {j - 1, j, j + 1};
            float redtotal = 0, greentotal = 0, bluetotal = 0;
            int count = 0;
            // Seeing the pixels around the main one
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    int currentRow = rowPlace[a];
                    int currentCol = colPlace[b];
                    // Verifying if the pixel is on the edge of the image
                    if (currentRow >= 0 && currentRow < height && currentCol >= 0 && currentCol < width)
                    {
                        redtotal += image[currentRow][currentCol].rgbtRed;
                        greentotal += image[currentRow][currentCol].rgbtGreen;
                        bluetotal += image[currentRow][currentCol].rgbtBlue;
                        count++;
                    }
                }
            }
            // Passing the blurred pixels to the temporary image
            temporary[i][j].rgbtRed = round(redtotal / count);
            temporary[i][j].rgbtGreen = round(greentotal / count);
            temporary[i][j].rgbtBlue = round(bluetotal / count);
        }
    }
    // Passing the pixels from the temporary image to the main one
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = temporary[r][c];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporary[height][width];
    
    // Defining the matrixes
    int Gx[3][3] = 
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
            
    int Gy[3][3] = 
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
            
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // Defining variables
            int rowPlace[] = {r - 1, r, r + 1};
            int colPlace[] = {c - 1, c, c + 1};
            float redX = 0, greenX = 0, blueX = 0, redY = 0, greenY = 0, blueY = 0;
            
            // Seeing the pixels around the main one
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    int currentRow = rowPlace[a];
                    int currentCol = colPlace[b];
                    
                    // Verifying if the pixel is on the edge of the image
                    if (currentRow >= 0 && currentRow < height && currentCol >= 0 && currentCol < width)
                    {
                        RGBTRIPLE px = image[currentRow][currentCol];
                        // Calculating RGB in X and Y 
                        redX += px.rgbtRed * Gx[a][b];
                        greenX += px.rgbtGreen * Gx[a][b];
                        blueX += px.rgbtBlue * Gx[a][b];
                        
                        redY += px.rgbtRed * Gy[a][b];
                        greenY += px.rgbtGreen * Gy[a][b];
                        blueY += px.rgbtBlue * Gy[a][b];
                        
                    }
                }
            }
            // Implementing the Sobel operator
            int redG = round(sqrt(redX * redX + redY * redY));
            int greenG = round(sqrt(greenX * greenX + greenY * greenY));
            int blueG = round(sqrt(blueX * blueX + blueY * blueY));
            
            // Loading the new pixels in the temporary image
            if (redG >= 255)
            {
                temporary[r][c].rgbtRed = 255;
            }
            else
            {
                temporary[r][c].rgbtRed = redG;  
            }
            
            if (greenG >= 255)
            {
                temporary[r][c].rgbtGreen = 255;
            }
            else
            {
                temporary[r][c].rgbtGreen = greenG;
            }
            
            if (blueG >= 255)
            {
                temporary[r][c].rgbtBlue = 255;
            }
            else
            {
                temporary[r][c].rgbtBlue = blueG;
            }
            
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temporary[i][j];
        }
    }
    return;
}
