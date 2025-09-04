#include <cs50.h>
#include <stdio.h>

int change_owed(void);

int main(void)
{
    int coins = 0;
    int value = 25;
    int i = 0;
    int change = change_owed();

    do
    { // Calculate how many quarters, dimes, nickels, and pennies are needed
        coins = coins + change / value;
        change = change % value;
        value = 10;
        if (i == 1)
        {
            value = 5;
        }
        else if (i == 2)
        {
            coins = coins + change;
            change = 0;
        }
        i++;
    }
    while (change != 0);
    printf("Number of coins: %i\n", coins);
}

// Prompt the user for the change until a positive integer is given
int change_owed(void)
{
    int number;
    do
    {
        number = get_int("Change owed: ");
    }
    while (number < 0);
    return number;
}
