#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
// How much change is owed?
    float change_d;   
    do 
    {
        printf("O hai! How much change is owed?\n");
        change_d = GetFloat();
    }
    while (change_d < 0.0);
    int change_c = round(change_d * 100);

// How many coins do we return according to the greedy algorithm?
    int coins = 0;
    
    while (change_c >= 25)
    {
        change_c = change_c - 25;
        coins = coins + 1;
    }        
    while (change_c >= 10)
    {
        change_c = change_c - 10;
        coins = coins + 1;
    }
    while (change_c >= 5)
    {
        change_c = change_c - 5;
        coins = coins + 1;
    }
    while (change_c >= 1)
    {
        change_c = change_c - 1;
        coins = coins + 1;
    } 
    
    printf("%i\n", coins);             
}
