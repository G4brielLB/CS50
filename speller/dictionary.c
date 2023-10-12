// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

int main(int argc, char *argv[]);
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// Maximum length (45) x (122) ASCII number of 'z'
const unsigned int N = 5490;

// Hash table
node *table[N];
// Total number of words
int total = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Check the words based on the index of hash function
    int index = hash(word);
    
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Calculating the index hash number and returning it
    int hash = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash += tolower(word[i]);
    }
    if (hash > N)
    {
        return hash % N;
    }
    else
    {
        return hash;
    }
    
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open and read the dictionary
    FILE *dict = fopen(dictionary, "r");
    char word[LENGTH + 1];
    if (!dict)
    {
        return false;
    }
    // Reading each single word
    while (fscanf(dict, "%s", word) != EOF)
    {
        node *new_word = malloc(sizeof(node));
        if (!new_word)
        {
            return false;
        }
        strcpy(new_word->word, word);
        new_word->next = NULL;
        
        int index = hash(word);
        if (!table[index])
        {
            table[index] = new_word;
        }
        else
        {
            new_word->next = table[index];
            table[index] = new_word;
        }
        total++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Returning the total of words
    return total;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Unload nodes to free memory
    for (int i = 0; i < N; i++)
    {
        node *header = table[i];
        node *cursor = header;
        node *temp = header;
        
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}
