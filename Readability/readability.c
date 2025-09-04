#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    float words = 1;
    int letters = 0;
    int sentences = 0;

    string text = get_string("Text: ");

    // Count words, letters, and sentences
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if ((text[i] == '!' || text[i] == '?' || text[i] == '.') && text[i - 1] != '.')
        {
            sentences++;
        }
    }

    // Compute the readability index
    float S = sentences * 100 / words;
    float L = letters * 100 / words;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    // Print the respective output
    if (index < 0.5)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 15.5)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}
