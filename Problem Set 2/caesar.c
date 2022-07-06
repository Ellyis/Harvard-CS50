#include "cs50.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // If 0 or 2 or more arguments are given
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        // exit program
        return 1;
    }

    // If only 1 argument is given
    // If argument contains other than digits
    if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        // exit program
        return 1;
    }

    // If argument fulfils criteria (numbers)

    // convert argument to int
    int key = atoi(argv[1]);

    // Prompt user for input
    string text = get_string("plaintext:  ");

    // Loop through each character in plaintext
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Rotate each character using key
        text[i] = rotate(text[i], key);
    }

    // Print ciphertext
    printf("ciphertext: %s\n", text);
    return 0;
}

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }

    return true;
}

char rotate(char c, int n)
{
    if (isupper(c))
    {
        c -= 'A'; // Get 0 for 'A', 1 for 'B' and so on
        c = (c + n) % 26; // Formula so that 'Z' can wrap to 'A'
        c += 'A'; // Convert back to ASCII code
        return c;
    }
    else if (islower(c))
    {
        c -= 'a'; // Get 0 for 'a', 1 for 'b' and so on
        c = (c + n) % 26; // Formula so that 'Z' can wrap to 'A'
        c += 'a'; // Convert back to ASCII code
        return c;
    }

    // Skip rotation if char is not alphabet
    return c;
}