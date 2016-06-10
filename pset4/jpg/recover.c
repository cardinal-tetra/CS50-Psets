/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
# include <stdio.h>
# include <stdlib.h>

int main(void)
{

    char title[8];
    unsigned char buffer[512];
    int counter = 0;
    FILE* img = NULL;

    // Open card file
    FILE* card = fopen("card.raw", "r");
    if (card == NULL)
    {
        fclose(card);
        printf("error\n");
        return 1; 
    }
    
    // Repeat until end of card
    while (fread(&buffer, 512, 1, card) == 1)
    {

        // Check for JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
              // Where we have found 000
            if (counter == 0)
            {
                sprintf(title, "00%d.jpg", counter);
                img = fopen(title, "w");
                counter++;
            }
              
              // Where we have found 001 - 010
             else if (counter > 0 && counter < 10)
            {
                fclose(img);
                sprintf(title, "00%d.jpg", counter);
                img = fopen(title, "w");
                counter++;
            }         
              
             // Where we have found JPEGs 010 - 015
             else if (counter >= 10)
            {
                fclose(img);
                sprintf(title, "0%d.jpg", counter);
                img = fopen(title, "w");
                counter++;
            }
        }
        
        // Write to file
        if (counter > 0)
        {
            fwrite(&buffer, 512, 1, img);
        }
        
    }
    
    // Close
    fclose(card);
    fclose(img);
    return 0;
}
