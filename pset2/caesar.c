#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{

// get the key

    if (argc != 2)
    { 
        printf("Please provide proper input\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    
    k = k % 26;

// get the plaintext

    string p = GetString();
    
// encipher and print

    for (int i = 0, n = strlen(p); i < n ; i++)
    {
        if (isalpha(p[i]))
        {
            if (isupper(p[i]))
            {
                int alph = ((p[i] - 65) + k) % 26;
                int asc = alph + 65;
                printf("%c",asc);
            }
            
            if (islower(p[i]))
            {
                int alph = ((p[i] - 97) + k) % 26;
                int asc = alph + 97;
                printf("%c",asc);
            }
        }
        else
        {
            printf("%c",p[i]);
        }        
    }

    printf("\n");
    
    return 0;
}
