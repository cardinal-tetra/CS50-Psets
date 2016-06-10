#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
// Prompt and retrieve name
    string name = GetString();

// Print out initials in capitals    
    printf("%c", toupper(name[0]));
    for(int i = 1, n = strlen(name); i < n; i++)
    {
        if (name[i] == ' ')
        {
            printf("%c", toupper(name[i + 1]));
        }           
    }
    printf("\n");
}
