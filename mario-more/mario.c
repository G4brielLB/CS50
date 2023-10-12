#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Getting the Height of Mario's Pyramid
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Defining the line
    for (int a = 0; a < height; a++)
    {
        // Defining the first part of pyramid
        int b = 0;
        for (b = 0; b < height;)
        {
            // Moving one character forward to print
            b++;
            // Printing blank spaces
            if (height - a > b)
            {
                printf(" ");
            }
            // Printing #
            else
            {
                printf("#");
            }
            
        }
        // Printing the gap
        printf("  ");
        // Printing the second part of pyramid
        for (int c = 0; c < a + 1; c++)
        {
            printf("#");
        }
        printf("\n");
    }

}