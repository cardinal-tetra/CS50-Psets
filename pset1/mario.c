#include <stdio.h>
#include <cs50.h>

int main(void)
{

// Get and validate height
    printf("please give a height no greater than 23\n");
    int height = GetInt();

    while (height < 0 || height > 23)
    {
        printf("please give a correct height\n");
        height = GetInt();
    }
    
// Generate half-pyramid
    for (int i = 0; i < height; i++)
    {
        int x = i + 2;
        while (x < (height + 1))
        {   
            printf(" ");
            x = x + 1;
        }
        int y = 0;
        int z = i + 2;
        while (y < z)
        {
            printf("#");
            y = y + 1;
        }
        printf("\n");
    }
}
