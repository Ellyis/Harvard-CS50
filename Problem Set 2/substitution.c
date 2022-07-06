#include "cs50.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool only_alphabets(string s);
bool repeated_characters(string s);
string encipher(string text, string key);

int main(int argc, string argv[])
{
    // If 0 or more than 2 arguments are given
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // If only 1 argument is given
    // Save argument as key
    string key = argv[1];

    // If length is not 26
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // If length is 26
    // If argument contains other than alphabets
    if (only_alphabets(key) == false)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }

    // If argument contains repeated characters
    if (repeated_characters(key) == true)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }

    // If argument is valid
    string text = get_string("plaintext:  ");

    string ciphertext = encipher(text, key);
    printf("ciphertext: %s\n", ciphertext);
}

// Check if string contains only alphabets
bool only_alphabets(string s)
{
    for (int i = 0; i < 26; i++)
    {
        if (isalpha(s[i]) == false)
        {
            return false;
        }
    }

    return true;
}

// Check if string has repeated characters
bool repeated_characters(string s)
{
    // Loop through each character excluding last one
    for (int i = 0; i < 26 - 1; i++)
    {
        // Loop through each character after the character at the outside loop
        for (int j = i + 1; j < 26; j++)
        {
            // Compare them regardless of case
            if (tolower(s[i]) == tolower(s[j]))
            {
                // Return true if character repeats
                return true;
            }
        }
    }
    // Return false if no repeating characters  
    return false;
}

// Encrypt plaintext to ciphertext using key
string encipher(string text, string key)
{
    // Loop through each character
    for (int i = 0, n = strlen(text); i < n; i++)
    {

        if (isupper(text[i]))
        {
            // Get distance of character from 'A'
            int index = text[i] -= 'A';

            // Substitute character to corresponding key by key[index] in upper case
            text[i] = toupper(key[index]);
        }
        else if (islower(text[i]))
        {
            // Get distance of character from 'a'
            int index = text[i] -= 'a';

            // Substitute character to corresponding key by key[index] in lower case
            text[i] = tolower(key[index]);
        }
    }

    return text;
}