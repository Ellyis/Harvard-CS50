#include "cs50.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
int get_grade(int letters, int words, int sentences);

int main(void)
{
    // Get text input from user
    string text = get_string("Text: ");

    // Count the number of letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Get the grade level using Coleman-Liau Index
    int grade = get_grade(letters, words, sentences);

    // Print out corresponding grades
    if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade >= 1)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Before Grade 1\n");
    }
}

int count_letters(string s)
{
    int count = 0;

    // Loop through each character in text
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Increment count if character is an alphabet
        if (isalpha(s[i]))
        {
            count++;
        }
    }

    return count;
}

int count_words(string s)
{
    int count = 1;

    // Loop through each character in text
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Increment count if character is a space
        if (isspace(s[i]))
        {
            count++;
        }
    }

    return count;
}

int count_sentences(string s)
{
    int count = 0;

    // Loop through each character in text
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Increment count if character is ".,!"
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            count++;
        }
    }

    return count;
}

int get_grade(int letters, int words, int sentences)
{
    // Average number of letters per 100 words
    float L = (float) letters / words * 100;

    // Average number of sentences per 100 words
    float S = (float) sentences / words * 100;

    // Coleman-Liau Index
    float index = 0.0588 * L - 0.296 * S - 15.8;

    return round(index);
}