#include "cs50.h"
#include <stdio.h>

// function to printf n times
void repeat(string s, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s", s);
    }
}

int main(void)
{
    int height;

    // ask for user input until height is within 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while (1 > height || height > 8);

    // loop for n times
    for (int i = 1; i <= height; i++)
    {
        // number of spaces for each row
        int j = height - i;

        // print spaces
        repeat(" ", j);

        // print left hashes
        repeat("#", i);

        //print gap
        printf("  ");

        // print right hashes
        repeat("#", i);

        // go to next row
        printf("\n");
    }
}