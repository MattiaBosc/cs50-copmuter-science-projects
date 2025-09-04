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

// Choose number of buckets in hash table
const unsigned int N = 5393;
unsigned int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int i = 0;
    int hash_word = hash(word);
    char lower_word[LENGTH + 1] = "";
    for (int n = strlen(word); i < n; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[i] = '\n';
    node *tmp = table[hash_word];
    while (tmp != NULL)
    {
        if (strcmp(tmp->word, lower_word) == 0)
        {
            return true;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        sum = sum + tolower(word[i]);
    }
    return (sum - 'a');
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }

    while (true)
    {
        // Read each word in the file
        int i = 0;
        char letter;
        char new_word[LENGTH + 1] = "";

        do
        {
            if (fread(&letter, sizeof(char), 1, input) == 0)
            {
                fclose(input);
                return true;
            }
            else
            {
                new_word[i] = letter;
                i++;
            }
        }
        while (letter != '\n');

        // Add each word to the hash table
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Not enough memory.\n");
            return false;
        }

        int hash_word = hash(new_word) - '\n';
        strcpy(new_node->word, new_word);
        new_node->next = table[hash_word];
        table[hash_word] = new_node;
        count++;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int j = 0;
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        while (tmp != NULL)
        {
            node *next = tmp->next;
            free(tmp);
            tmp = next;
        }
        if (tmp != NULL)
        {
            j++;
        }
    }

    if (j == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
