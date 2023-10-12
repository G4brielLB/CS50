#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

const int CHUNK = 512;

int main(int argc, char *argv[])
{
    // Check command-line argument
    if (argc != 2)
    {
        printf("Usage ./recover card.raw\n");
        return 1;
    }
    
    // Open file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    // Defining variables
    uint8_t block[CHUNK];
    size_t read_chunks;
    int count = 0;
    char jpeg[100];
    FILE *currentJpeg;
    bool first_jpeg = false;
    bool found_jpeg = false;
    // Read the memory card
    while (fread(block, sizeof(BYTE), CHUNK, card))
    {
        // Verifies the start of a new jpeg
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            found_jpeg = true;
            // Verifies if it is the first jpeg
            if (!first_jpeg)
            {
                first_jpeg = true;
            }
            // Close a Jpeg to start a new one
            else
            {
                fclose(currentJpeg);
            }
            sprintf(jpeg, "%03i.jpg", count);
            currentJpeg = fopen(jpeg, "w");
            fwrite(block, sizeof(BYTE), CHUNK, currentJpeg);
            count++;
        }
        // Keeps writing the jpeg because a new one was not found.
        else
        {
            if (found_jpeg)
            {
                fwrite(block, sizeof(BYTE), CHUNK, currentJpeg);
            }
        }
    }
    // Closes the files
    fclose(currentJpeg);
    fclose(card);
    return 0;
}