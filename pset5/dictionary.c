/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"
#include <string.h>

// Declare recursion function
void recursion();

// Create node
    typedef struct node
    {
        bool is_word;
        struct node* children[27];        
    }
    node; 
    
    node* root;
    
    int words = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{

    node* crawler = root;
    
    for(int i = 0, n = strlen(word); i <= n; i++)
    {
        if (word[i] == '\0')
        {
            if (crawler->is_word == true)
            {
                return true;
            }
            else
            {
                return false;
            }
           
        }
        
        else if (isalpha(word[i]))
        {
            if (crawler->children[tolower(word[i]) - 'a'] == NULL)
            {
                return false;
            }
            else
            {
                crawler = crawler->children[tolower(word[i]) - 'a'];
            }                
        }
        
        else if (word[i] == '\'')
        {
            if (crawler->children['\'' - 13] == NULL)
            {
                return false;
            }
            else
            {
                crawler = crawler->children['\'' - 13];
            }
        }  
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{   
    // Open dictionary
    FILE* cidian = fopen(dictionary, "r");    
    if (cidian == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }
    
    // Set aside memory for pointers
    root = calloc(1, sizeof(node));
    node* trav = root;

    // Read into dictionary
    for (int c = fgetc(cidian); c != EOF; c = fgetc(cidian))
    {
        if (isalpha(c))
        {
            if (trav->children[c - 'a'] == NULL)
            {
                trav->children[c - 'a'] = calloc(1, sizeof(node));
            }
            trav = trav->children[c - 'a'];       
        }
        
        else if  (c == '\'')
        {
            if (trav->children[c - 13] == NULL)
            {
                trav->children[c - 13] = calloc(1, sizeof(node));                
            } 
            trav = trav->children[c - 13];
        }
        
        else if (trav != root)
        {   
            trav->is_word = true;
            words++;     
            trav = root;       
        }       
    }
    fclose(cidian);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    recursion(root);
    return true; 
}

// rescursive search function
void recursion(struct node* root)
{
    for (int i = 0; i < 27; i++)
    {
        if (root->children[i] != NULL)
        {
            recursion(root->children[i]);
        }
    }
    free(root);
}

