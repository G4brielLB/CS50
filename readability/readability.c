#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Getting the text from the User
    string text = get_string("Text: ");
    // Defining the variables
    float letters = 0, words = 1, sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char digit = toupper(text[i]);
        // Checking letters, words and sentences
        if ('A' <= digit && 'Z' >= digit)
        {
            letters++;
        }
        else if (digit == ' ')
        {
            words++;
        }
        else if (digit == '.' || digit == '?' || digit == '!')
        {
            sentences++;
        }
    }
    // Calculating the index
    long double l = letters * 100 / words, s = sentences * 100 / words;
    int index = round(l * 0.0588 - s * 0.296 - 15.8);
    // Output
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}