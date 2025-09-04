#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int only_digits(string arg);
string rotate(string text, int key);

int main(int argc, string argv[])
{
    // Check the function argument(s) for correctness
    if (argc != 2 || only_digits(argv[1]) == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert a string to an int
    int key = atoi(argv[1]);

    string text = get_string("plaintext:  ");

    text = rotate(text, key);

    printf("ciphertext: %s\n", text);

    return 0;
}

// Check if the function argument is only numerical
int only_digits(string arg)
{
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        if (arg[i] < '0' || arg[i] > '9')
        {
            return 1;
        }
    }
    return 0;
}

// Rotate letters only
string rotate(string text, int key)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]))
        {
            text[i] = (((text[i] + key) - 'A') % 26) + 'A';
        }
        else if (islower(text[i]))
        {
            text[i] = (((text[i] + key) - 'a') % 26) + 'a';
        }
    }
    return text;
}
