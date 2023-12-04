// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

unsigned int word_count;
unsigned int hash_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Obtain the hash value
    hash_value = hash(word);

    // acces the table
    node *cursor = table[hash_value];

    // go through list
    while(cursor != NULL)
    {
        //check if the word matches
        if(strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        // move it to the next node
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Hash called djb2 created by Dan Bernstein
    unsigned long hash = 5381;
    int c;

    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash + c);
    }
    return hash % N;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // open file dictionary
    FILE *file = fopen(dictionary, "r");
    //return false if file is NULL
    if(file == NULL)
    {
        printf("File Cannot be found");

        return false;
    }

    // delcare variable called word
    char word[LENGTH + 1];

    // Scan dictionary for string up until EOF
    while(fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory
        node *n = malloc(sizeof(node));

        // return if word is NULL
        if(n == NULL)
        {
            return false;
        }

        //copy into node
        strcpy(n->word,word);
        hash_value = hash(word);
        n->next = table[hash_value];
        table[hash_value] = n;
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
    // check each node
    for(int i = 0; i < N; i++)
    {
        // set cursor to each location
        node *cursor = table[i];

        // free memory if cursor is not null
        if(cursor != NULL)
        {
            //create a temp for the cursor
            node *tmp = cursor;
            //move cursor to the next node
            cursor = cursor->next;
            //free temp
            free(tmp);
        }

        // IF cursor is NULL
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }

    }
    return false;
}
