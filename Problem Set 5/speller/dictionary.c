// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Variables
unsigned int word_count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hash_value = hash(word);

    // Point cursor to the first node of array
    node *cursor = table[hash_value];

    // Traverse through the linked list
    while (cursor != NULL)
    {
        // If word exists in dictionary
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        // Else: move cursor to next node
        cursor = cursor->next;
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
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Failed to open dictionary file\n");
        return false;
    }
    char word[LENGTH + 1];

    // Search for words until EOF
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy word to new node
        strcpy(n->word, word);

        // Get hash value of word
        unsigned int hash_value = hash(word);

        // Set pointer of new node to current head of table
        n->next = table[hash_value];

        // Set new node as head of table
        table[hash_value] = n;

        // Increment word count
        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        // If the loop has traversed through the whole array and to the end of the linked list
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
