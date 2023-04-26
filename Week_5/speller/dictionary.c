// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
//include strcasecmp...etc
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"
// count word
int wordCount = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

/*
Your job, ultimately,
is to re-implement those functions as cleverly
as possible so that this spell checker works as advertised.
And fast!
*/

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int targ = hash(word);
    node *cursor = table[targ];

    if (table[targ] == NULL)
    {
        return false;
    }

    while (1)
    {
        if (strcasecmp(cursor->word,word) == 0)
        {
            return true;
        }
        if (cursor->next == NULL)
        {
            return false;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return ((toupper(word[0]) - 'A') + 5)%26;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *t = malloc(sizeof(node));
        // t = malloc(sizeof(node));
        strcpy(t->word, word);
        t->next = NULL;
        if (t == NULL)
        {
            return false;
        }

        int hashNum = hash(word);

        if (table[hashNum] == NULL)
        {
            table[hashNum] = t;
        }
        else
        {
            node *cursor;
            cursor = table[hashNum];
            while (1)
            {
                if (cursor->next == NULL)
                {
                    /* t = malloc(sizeof(node));
                    strcpy(t->word, word);
                    t->next = NULL; */
                    cursor->next = t;
                    break;
                }
                else
                {
                    cursor = cursor->next;
                }
            }
        }
        wordCount++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            if (table[i]->next != NULL)
            {
                free(table[i]->next);
            }
            free(table[i]);
        }
    }

    return true;
}
