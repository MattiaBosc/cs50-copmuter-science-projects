#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;
const int IMAGES = 50;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];
    int count = 0;
    char *image_name[IMAGES];
    for (int i = 0; i < IMAGES; i++)
    {
        image_name[i] = (char *) malloc(8 * sizeof(char));
        if (image_name[i] == NULL)
        {
            printf("Not enough memory.\n");
            return 1;
        }
        if (i < 10)
        {
            sprintf(image_name[i], "00%i.jpg", i);
        }
        else
        {
            sprintf(image_name[i], "0%i.jpg", i);
        }
    }

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCK_SIZE, input) == 512)
    {
        // Create JPEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0)
        {
            FILE *output = fopen(image_name[count], "a+");
            if (output == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }
            fwrite(buffer, BLOCK_SIZE, 1, output);
            fclose(output);
            count++;
        }
        else if (count > 0)
        {
            FILE *output = fopen(image_name[count - 1], "a+");
            if (output == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }
            fwrite(buffer, BLOCK_SIZE, 1, output);
            fclose(output);
        }
    }

    for (int i = 0; i < IMAGES; i++)
    {
        free(image_name[i]);
    }
    fclose(input);
    return 0;
}
