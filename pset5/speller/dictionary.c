// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int h = hash(word);
    for (node *ptr = table[h]; ptr != NULL; ptr = ptr->next)
    {
        for (int i = 0, n = strlen(word), d = strlen(ptr->word); i < n; i++)
        {
            if (d != n)
            {
                break;
            }
            if (toupper(ptr->word[i]) != toupper(word[i]))
            {
                break;
            }
            else if (toupper(ptr->word[i]) == toupper(word[i]))
            {
                if (i == (n - 1))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // file dictionary open
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        int i = 0;
        while (word[i] != '\0')
        {
            n->word[i] = word[i];
            i++;
        }
        n->word[i] = '\0';
        // upload in hash table
        int h = hash(n->word);
        n->next = table[h];
        table[h] = n;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int size = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *ptr = table[i]; ptr != NULL; ptr = ptr->next)
        {
            size++;
        }
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *buffer = NULL;

    for (int i = 0; i < N; i++)
    {
        for (node *ptr = table[i]; ptr != NULL; ptr = buffer)
        {
            buffer = ptr->next;
            free(ptr);
        }
    }
    if (buffer == NULL)
    {
        return true;
    }
    return false;
}
