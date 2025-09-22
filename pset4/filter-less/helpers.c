#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int a =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = a;
            image[i][j].rgbtGreen = a;
            image[i][j].rgbtRed = a;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +
                             0.189 * image[i][j].rgbtBlue);
            int sGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +
                               0.168 * image[i][j].rgbtBlue);
            int sBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +
                              0.131 * image[i][j].rgbtBlue);
            if (sRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sRed;
            }
            if (sGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sGreen;
            }
            if (sBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int tempr = 0, tempg = 0, tempb = 0;
            tempr = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = tempr;

            tempg = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = tempg;

            tempb = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = tempb;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
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
            int sumr = copy[i][j].rgbtRed;
            int sumg = copy[i][j].rgbtGreen;
            int sumb = copy[i][j].rgbtBlue;
            int count = 1;
            if ((i - 1) >= 0)
            {
                sumr += copy[i - 1][j].rgbtRed;
                sumg += copy[i - 1][j].rgbtGreen;
                sumb += copy[i - 1][j].rgbtBlue;
                count++;

                if ((j - 1) >= 0)
                {
                    sumr += copy[i - 1][j - 1].rgbtRed;
                    sumg += copy[i - 1][j - 1].rgbtGreen;
                    sumb += copy[i - 1][j - 1].rgbtBlue;
                    count++;
                }

                if ((j + 1) < width)
                {
                    sumr += copy[i - 1][j + 1].rgbtRed;
                    sumg += copy[i - 1][j + 1].rgbtGreen;
                    sumb += copy[i - 1][j + 1].rgbtBlue;
                    count++;
                }
            }

            if ((i + 1) < height)
            {
                sumr += copy[i + 1][j].rgbtRed;
                sumg += copy[i + 1][j].rgbtGreen;
                sumb += copy[i + 1][j].rgbtBlue;
                count++;

                if ((j - 1) >= 0)
                {
                    sumr += copy[i + 1][j - 1].rgbtRed;
                    sumg += copy[i + 1][j - 1].rgbtGreen;
                    sumb += copy[i + 1][j - 1].rgbtBlue;
                    count++;
                }

                if ((j + 1) < width)
                {
                    sumr += copy[i + 1][j + 1].rgbtRed;
                    sumg += copy[i + 1][j + 1].rgbtGreen;
                    sumb += copy[i + 1][j + 1].rgbtBlue;
                    count++;
                }
            }

            if ((j - 1) >= 0)
            {
                sumr += copy[i][j - 1].rgbtRed;
                sumg += copy[i][j - 1].rgbtGreen;
                sumb += copy[i][j - 1].rgbtBlue;
                count++;
            }
            if ((j + 1) < width)
            {
                sumr += copy[i][j + 1].rgbtRed;
                sumg += copy[i][j + 1].rgbtGreen;
                sumb += copy[i][j + 1].rgbtBlue;
                count++;
            }

            image[i][j].rgbtRed = round((float) sumr / (float) count);
            image[i][j].rgbtGreen = round((float) sumg / (float) count);
            image[i][j].rgbtBlue = round((float) sumb / (float) count);
        }
    }
    return;
}
