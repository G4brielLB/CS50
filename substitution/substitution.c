#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Getting the key from the user
int main(int argc, string argv[])
{
    // Verifying if there is a key with 26 characters
    if (argc == 2 && strlen(argv[1]) == 26)
    {
        string key = argv[1];
        for (int i = 0; i < 26; i++)
        {
            char digit = key[i];
            // Verifying if the key has just alphabetical characters
            if (!isalpha(digit))
            {
                printf("ERROR! The key has to have just alphabetichal characters!\n");
                return 1;
            }
            // Verifying if the key has repeated characters
            for (int a = 0, ver = 0; a < 26; a++)
            {
                if (toupper(digit) == toupper(key[a]))
                {
                    ver++;
                }
                if (ver > 1)
                {
                    printf("ERROR! You can not repeat a character!\n");
                    return 1;
                }
            }
        }
        // Getting the plaintext
        string plaintext = get_string("Plaintext: ");
        // Preparing variables
        const int n = strlen(plaintext);
        int text[n];
        // Printing the output
        printf("ciphertext: ");
        // Criptography
        for (int i = 0; i < n; i++)
        {
            char letter = plaintext[i];
            if (isupper(letter))
            {
                int index = letter - 65;
                printf("%c", toupper(key[index]));
            }
            else if (islower(letter))
            {
                int index = letter - 97;
                printf("%c", tolower(key[index]));
            }
            else
            {
                int index = letter;
                printf("%c", letter);
            }
            // text[i] = plaintext[i];
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("ERROR! You have to write a key with 26 characters\n");
        return 1;
    }
}