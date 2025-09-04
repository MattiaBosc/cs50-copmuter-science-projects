#include <cs50.h>
#include <stdio.h>

int ask_height(void);

int main(void)
{
    int height = ask_height();

    // Print a pyramid with height 'height'
    for (int i = 0; i < height; i++)
    {
        // Print '#' or ' ' depending on the row that is being built
        for (int j = 0; j < height; j++)
        {
            if (j < height - i - 1)
                printf(" ");
            else
                printf("#");
        }
        printf("\n");
    }
}

// Prompt the user for the pyramid's height until a positive integer is given
int ask_height(void)
{
    int number;
    do
    {
        number = get_int("How tall do you want the pyramid to be? ");
    }
    while (number < 1);
    return number;
}
