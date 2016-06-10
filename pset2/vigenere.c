#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    // Enter cipher key and check if it is correct
    
    if (argc != 2)
    {
        printf("Invalid\n");
        return 1;
    }
    
    string k = argv[1];
    
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (isalpha(k[i]) == false)
        {
            printf("Invalid\n");
            return 1;
        }
    }
    
    // Plaintext and counter
    
    string p = GetString();
    
    int c = 0; 
    
    // Encipher     
    
    for (int i = 0, n = strlen(p); i < n; i++)
    {   
        if (isalpha(p[i]))
        {
            int j = strlen(k);
            if (isupper(p[i]) && isupper(k[(i - c) % j]))
            {
                int alph = ((p[i] - 65) + (k[(i - c) % j] - 65)) % 26;
                int asc = alph + 65;
                printf ("%c",asc);
            }
            if (isupper(p[i]) && islower(k[(i - c) % j]))
            {
                int alph = ((p[i] - 65) + (k[(i - c) % j] - 97)) % 26;
                int asc = alph + 65;
                printf ("%c",asc);
            }
            if (islower(p[i]) && isupper(k[(i - c) % j]))
            {
                int alph = ((p[i] - 97) + (k[(i - c) % j] - 65)) % 26;
                int asc = alph + 97;
                printf ("%c",asc);
             }
            if (islower(p[i]) && islower(k[(i - c) % j]))
            {
                int alph = ((p[i] - 97) + (k[(i - c) % j] - 97)) % 26;
                int asc = alph + 97;
                printf ("%c",asc);
            }
        }    
        else
        {
            printf("%c",p[i]);
            c = c + 1; 
        }
    }
    
    printf("\n");
    
    return 0;
}
