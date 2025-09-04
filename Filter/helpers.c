#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average = 0;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int max_value = 255;
    int Sepia_Red, Sepia_Green, Sepia_Blue;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            Sepia_Red = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            Sepia_Green = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            Sepia_Blue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // Ensure the resulting value is no larger than 255
            if (Sepia_Red > max_value)
            {
                Sepia_Red = max_value;
            }
            if (Sepia_Green > max_value)
            {
                Sepia_Green = max_value;
            }
            if (Sepia_Blue > max_value)
            {
                Sepia_Blue = max_value;
            }

            // Update pixel with sepia values
            image[i][j].rgbtRed = Sepia_Red;
            image[i][j].rgbtGreen = Sepia_Green;
            image[i][j].rgbtBlue = Sepia_Blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE placeholder;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap red pixels
            placeholder = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = placeholder;

            // Swap green pixels
            placeholder = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = placeholder;

            // Swap blue pixels
            placeholder = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = placeholder;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average_red, average_green, average_blue, a, b, c, d;
            float count = 0;
            average_red = average_green = average_blue = 0;
            a = c = -1;
            b = d = 2;

            // Check for borders
            if (i == 0)
            {
                a = 0;
            }
            else if (i == height - 1)
            {
                b = 1;
            }
            if (j == 0)
            {
                c = 0;
            }
            else if (j == width - 1)
            {
                d = 1;
            }

            // Average colour for each pixel
            for (int k = a; k < b; k++)
            {
                for (int l = c; l < d; l++)
                {
                    average_red = average_red + (int) copy[i + k][j + l].rgbtRed;
                    average_green = average_green + (int) copy[i + k][j + l].rgbtGreen;
                    average_blue = average_blue + (int) copy[i + k][j + l].rgbtBlue;
                    count++;
                }
            }
            image[i][j].rgbtRed = round(average_red / count);
            image[i][j].rgbtGreen = round(average_green / count);
            image[i][j].rgbtBlue = round(average_blue / count);
        }
    }
    return;
}
