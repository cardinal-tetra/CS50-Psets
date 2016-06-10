/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // counter for even numbers
    int m = 0;
    // find midpoint
    if ((n % 2) == 0)
    {
        n = n / 2;
        m = m + 1;
    }
    else
    {
        n = (n - 1) / 2;
    }
    
    // Open book and find value
    if (values[n] == value)
    {
        return true;
    }
    // Value should be towards left
    if (values[n] > value && n != 0)
    {
        return search(value, values, n);        
    }
    
    if (values[0] > value)
    {
        return false;
    }
    
    // Value should be towards right
    if (values[n] < value && n != 0)
    {
        for (int i = 0, j = n - m + 1; i < n; i++, j++)  
        {            
            values[i] = values[j]; 
        }
        return search(value, values, n);
    }
    
    if (values[0] < value)
    {
        return false;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = 0; i < (n - 1); i++)  
    {
        for (int i = 0; i < (n - 1); i++)
        {
            if (values[i] > values[i + 1])
            {
                int tmp = values[i + 1];
                values[i + 1] = values[i];
                values[i] = tmp;
            }
        }
    }       
}
