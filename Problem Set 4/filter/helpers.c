#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get average of RGB values and round off to nearest int
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.00);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // 5 elements in a column requires only 2 swaps as middle can be left untouched
        for (int j = 0; j < width / 2; j++)
        {

            // temp = a
            RGBTRIPLE temp = image[i][j];

            // a = b
            image[i][j] = image[i][width - 1 - j];

            // b = temp
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed, sumGreen, sumBlue, counter;
            sumRed = sumGreen = sumBlue = counter = 0;

            // Get neighbouring pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    // Check if pixel is within image boundary
                    if (currentX >= 0 && currentX < height && currentY >= 0 && currentY < width)
                    {
                        // Add RGB values to sum
                        sumRed += image[currentX][currentY].rgbtRed;
                        sumGreen += image[currentX][currentY].rgbtGreen;
                        sumBlue += image[currentX][currentY].rgbtBlue;

                        counter++;
                    }
                }

            }
            // Calculate average of neighbouring pixels
            temp[i][j].rgbtRed = round((float) sumRed / counter);
            temp[i][j].rgbtGreen = round((float) sumGreen / counter);
            temp[i][j].rgbtBlue = round((float) sumBlue / counter);
        }
    }
    // Update original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Initialize Gx and Gy
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // // Loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redX, greenX, blueX, redY, greenY, blueY;
            redX = greenX = blueX = redY = greenY = blueY = 0;

            // Get neighbouring pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    // Check if pixel is within image boundary
                    if (currentX >= 0 && currentX < height && currentY >= 0 && currentY < width)
                    {
                        // Calculate Gx for RGB
                        redX += image[currentX][currentY].rgbtRed * Gx[x + 1][y + 1];
                        greenX += image[currentX][currentY].rgbtGreen * Gx[x + 1][y + 1];
                        blueX += image[currentX][currentY].rgbtBlue * Gx[x + 1][y + 1];

                        // Calculate Gx for RGB
                        redY += image[currentX][currentY].rgbtRed * Gy[x + 1][y + 1];
                        greenY += image[currentX][currentY].rgbtGreen * Gy[x + 1][y + 1];
                        blueY += image[currentX][currentY].rgbtBlue * Gy[x + 1][y + 1];
                    }
                }
            }
            // Calculate square root of Gx^2 + Gy^2
            int red = round(sqrt((redX * redX) + (redY * redY)));
            int green = round(sqrt((greenX * greenX) + (greenY * greenY)));
            int blue = round(sqrt((blueX * blueX) + (blueY * blueY)));

            // Cap value at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            // Update copy
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtBlue = blue;
        }
    }
    // Update original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
}
